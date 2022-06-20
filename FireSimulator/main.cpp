#include <iostream>
#include <array>
#include <vector>
#include "Constants.h"
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include <thread>


using namespace std;

static const double pi = 3.14159265;
const int mesh_size = 100;


void calculateFront(vector<vector<shared_ptr<Cell>>> tiles, int x_burn, int y_burn) {
	//double x_burn, y_burn;		// начальные координаты точки горени€
	double a, b, c;				// мала€ полуось (a), больша€ полуось(b), рассто€ние до центра эллипса(c) от начальной точки горени€
	double wind_factor;			// скорость распространени€ фронта пожара по модели –отермела
	double wind_speed = 2;		// скорость ветра м/с
	double wind_angle = 0;		// направление ветра, рассчитываемое в градусах

	// константы, необходимые дл€ расчЄта скорости распространени€ фронта пожара
	// на данный момент соответстуют местности с кодом 303 (лишайники, сосновый лес редкий, деревь€ молодые и средневозрастные)
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

	double LB, HB;				// переменные дл€ расчЄта формы эллипса
	LB = 0.936 * exp(0.2566 * wind_speed) + 0.461 * exp(-0.1548 * wind_speed) - 0.397;
	HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));

	b = (wind_factor / 2) * ((1 + HB) / HB);
	a = b / LB;
	c = b - (wind_factor / LB);

	//cout << a << "   " << b << "   " << c << endl;

	for (int y = 0; y < mesh_size; y++) {
		for (int x = 0; x < mesh_size; x++) {
			double rotated_x = (double(x - x_burn) / 100 - c * cos(wind_angle * pi / 180)) * cos(wind_angle * pi / 180) + // поворот в сторону направлени€ ветра
				double(y - y_burn - c * sin(wind_angle * pi / 180)) / 100 * sin(wind_angle * pi / 180);
			double rotated_y = double(y - y_burn - c * sin(wind_angle * pi / 180)) / 100 * cos(wind_angle * pi / 180) -
				(double(x - x_burn) / 100 - c * cos(wind_angle * pi / 180)) * sin(wind_angle * pi / 180);

			if ((pow(rotated_y, 2) / pow(a, 2) + pow(rotated_x, 2) / pow(b, 2)) <= 1) {
				tiles[y][x]->state = BurnState::on_fire;
			}
		}
	}
}



int main() {
	vector<vector<shared_ptr<Cell>>> tiles;
	tiles.resize(mesh_size);

	for (int i = 0; i < mesh_size; i++) {
		tiles[i].resize(mesh_size);
		for (int j = 0; j < mesh_size; j++) {
			tiles[i][j] = make_shared<Cell>(Tile::forest);
		}
	}

	vector<pair<int, int>> points;
	calculateFront(tiles, 10, 10);
	calculateFront(tiles, 20, 10);
	calculateFront(tiles, 30, 10);

	sf::RenderWindow window(sf::VideoMode(600, 700), "Fire Simulator");

	vector<vector<sf::RectangleShape>> rectangles;
	rectangles.resize(mesh_size);
	const int rect_size = window.getSize().x / mesh_size;
	for (int i = 0; i < mesh_size; i++) {
		rectangles[i].resize(mesh_size);
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

		for (int y = 0; y < mesh_size; y++) {
			for (int x = 0; x < mesh_size; x++) {
				if (tiles[y][x]->state == BurnState::on_fire) {
					rectangles[x][y].setFillColor(sf::Color::Red);
				}
			}
		}

		for (int y = 0; y < mesh_size; y++) {
			for (int x = 0; x < mesh_size; x++) {
				if (tiles[y][x]->state == BurnState::on_fire) {
					points.push_back(make_pair(x, y));
				}
			}
		}

		for (auto& point : points) {
			calculateFront(tiles, point.first, point.second);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	return 0;

}