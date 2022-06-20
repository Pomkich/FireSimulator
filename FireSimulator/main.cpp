#include <iostream>
#include <array>
#include <vector>
#include "Constants.h"
#include "Cell.h"
#include "SFML/Graphics.hpp"


using namespace std;

static const double pi = 3.14159265;
const int mesh_size = 40;

array<array<Cell, mesh_size>, mesh_size>
calculateFront(array<array<Cell, mesh_size>, mesh_size> tiles, int x_burn, int y_burn) {
	//double x_burn, y_burn;		// ��������� ���������� ����� �������
	double a, b, c;				// ����� ������� (a), ������� �������(b), ���������� �� ������ �������(c) �� ��������� ����� �������
	double wind_factor;			// �������� ��������������� ������ ������ �� ������ ���������
	double wind_speed = 2;		// �������� ����� �/�
	double wind_angle = 180;		// ����������� �����, �������������� � ��������

	// ���������, ����������� ��� ������� �������� ��������������� ������ ������
	// �� ������ ������ ������������ ��������� � ����� 303 (���������, �������� ��� ������, ������� ������� � ����������������)
	double fuel_load = 1.7;				// w0
	double fuel_depth = 0.12;			// delta
	double stv_ratio = 2000;			// sigma
	double particle_dens = 300;			// p

	double B = 0.0133 * pow(stv_ratio, 0.54);
	double C = 7.47 * exp(-0.0693 * pow(stv_ratio, 0.55));
	double E = 0.715 * exp(-0.0001079 * stv_ratio);

	double packing_ratio = fuel_load / fuel_depth / particle_dens;	// beta
	double opm_packing_ratio = 3.348 * pow(stv_ratio, -0.8189);		// beta op

	wind_factor = C * pow(wind_speed, B) * pow((packing_ratio / opm_packing_ratio), -E);

	double LB, HB;				// ���������� ��� ������� ����� �������
	LB = 0.936 * exp(0.2566 * wind_speed) + 0.461 * exp(-0.1548 * wind_speed) - 0.397;
	HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));

	b = (wind_factor / 2) * ((1 + HB) / HB);
	a = b / LB;
	c = b - (wind_factor / LB);

	//cout << a << "   " << b << "   " << c << endl;

	for (int y = 0; y < mesh_size; y++) {
		for (int x = 0; x < mesh_size; x++) {
			double rotated_x = (double(x - x_burn) / 100 - c * cos(wind_angle * pi / 180)) * cos(wind_angle * pi / 180) + // ������� � ������� ����������� �����
				double(y - y_burn - c * sin(wind_angle * pi / 180)) / 100 * sin(wind_angle * pi / 180);
			double rotated_y = double(y - y_burn - c * sin(wind_angle * pi / 180)) / 100 * cos(wind_angle * pi / 180) -
				(double(x - x_burn) / 100 - c * cos(wind_angle * pi / 180)) * sin(wind_angle * pi / 180);

			if ((pow(rotated_y, 2) / pow(a, 2) + pow(rotated_x, 2) / pow(b, 2)) <= 1) {
				tiles[y][x].state = BurnState::on_fire;
			}
		}
	}

	/*for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			cout << static_cast<int>(tiles[i][j].state) << " ";
		}
		cout << endl;
	}
	cout << "=========================================" << endl;
	*/
	return tiles;
}



int main() {
	array<array<Cell, mesh_size>, mesh_size> tiles;

	for (int i = 0; i < mesh_size; i++) {
		for (int j = 0; j < mesh_size; j++) {
			tiles[i][j] = Cell(Tile::forest);
		}
	}

	vector<pair<int, int>> points;

	tiles = calculateFront(tiles, 10, 10);

	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < mesh_size; y++) {
			for (int x = 0; x < mesh_size; x++) {
				if (tiles[y][x].state == BurnState::on_fire) {
					points.push_back(make_pair(x, y));
				}
			}
		}

		for (auto& point : points) {
			tiles = calculateFront(tiles, point.first, point.second);
		}

		for (int c = 0; c < mesh_size; c++) {
			for (int j = 0; j < mesh_size; j++) {
				cout << static_cast<int>(tiles[c][j].state) << " ";
			}
			cout << endl;
		}
		cout << "=========================================" << endl;
		
		points.clear();
	}



	sf::RenderWindow window(sf::VideoMode(600, 700), "Fire Simulator");

	array<array<sf::RectangleShape, mesh_size>, mesh_size> rectangles;
	const int rect_size = window.getSize().x / mesh_size;
	for (int i = 0; i < mesh_size; i++) {
		for (int j = 0; j < mesh_size; j++) {
			rectangles[i][j].setPosition(i*rect_size, j* rect_size + 100);
			rectangles[i][j].setFillColor(sf::Color::Green);
			rectangles[i][j].setOutlineColor(sf::Color::Black);
			rectangles[i][j].setOutlineThickness(2);
			rectangles[i][j].setSize(sf::Vector2f(rect_size, rect_size));
		}
	}

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);

		for (int i = 0; i < mesh_size; i++) {
			for (int j = 0; j < mesh_size; j++) {
				window.draw(rectangles[i][j]);

			}
		}
		window.display();
	}

	return 0;

}