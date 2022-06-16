#include <iostream>
#include <array>
#include <vector>
#include "Constants.h"
#include "Cell.h"

using namespace std;

static const double pi = 3.14159265;

array<array<Cell, 20>, 20> calculateFront(array<array<Cell, 20>, 20> tiles, int x_burn, int y_burn) {
	//double x_burn, y_burn;		// начальные координаты точки горени€
	double a, b, c;				// мала€ полуось (a), больша€ полуось(b), рассто€ние до центра эллипса(c) от начальной точки горени€
	double wind_factor;			// скорость распространени€ фронта пожара по модели –отермела
	double wind_speed = 2;		// скорость ветра м/с
	double wind_angle = 180;		// направление ветра, рассчитываемое в градусах

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

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			double rotated_x = (double(x - x_burn) / 100 - c * cos(wind_angle * pi / 180)) * cos(wind_angle * pi / 180) + // поворот в сторону направлени€ ветра
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
	array<array<Cell, 20>, 20> tiles;
	int start_tiles[20][20] = {
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
	};

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			tiles[i][j] = Cell(static_cast<Tile>(start_tiles[i][j]));
		}
	}

	vector<pair<int, int>> points;

	tiles = calculateFront(tiles, 10, 10);

	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				if (tiles[y][x].state == BurnState::on_fire) {
					points.push_back(make_pair(x, y));
				}
			}
		}

		for (auto& point : points) {
			tiles = calculateFront(tiles, point.first, point.second);
		}

		for (int c = 0; c < 20; c++) {
			for (int j = 0; j < 20; j++) {
				cout << static_cast<int>(tiles[c][j].state) << " ";
			}
			cout << endl;
		}
		cout << "=========================================" << endl;
		
		points.clear();
	}
	

	return 0;
}