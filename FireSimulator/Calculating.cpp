#include "Calculating.h"

using namespace std;

void calculateFront(vector<vector<shared_ptr<Cell>>>& tiles, int x_burn, int y_burn) {
	double a, b, c;				// малая полуось (a), большая полуось(b), расстояние до центра эллипса(c) от начальной точки горения
	double wind_factor;			// скорость распространения фронта пожара по модели Ротермела
	double wind_speed = tiles[x_burn][y_burn]->wind_speed;		// скорость ветра м/с
	double wind_angle = tiles[x_burn][y_burn]->wind_angle;		// направление ветра, рассчитываемое в градусах

	wind_factor = Constants::C * pow(wind_speed, Constants::B) * 
		pow((Constants::packing_ratio / Constants::opm_packing_ratio), -Constants::E);

	double LB, HB;				// переменные для расчёта формы эллипса
	LB = 0.936 * exp(0.2566 * wind_speed) + 0.461 * exp(-0.1548 * wind_speed) - 0.397;
	HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));

	b = (wind_factor / 2) * ((1 + HB) / HB);
	a = b / LB;
	c = b - (wind_factor / LB);

	// проверяем только в 1/10 от площади а не всей сетки для оптимизации
	int height_min = (y_burn - 10) > 0 ? y_burn - 10 : 0;
	int height_max = (y_burn + 10) < Constants::mesh_size ? y_burn + 10 : Constants::mesh_size;
	int width_min = (x_burn - 10) > 0 ? x_burn - 10 : 0;
	int width_max = (x_burn + 10) < Constants::mesh_size ? x_burn + 10 : Constants::mesh_size;

	for (int y = height_min; y < height_max; y++) {
		for (int x = width_min; x < width_max; x++) {
			double rotated_x = (double(x - x_burn) / 100 - c * cos(wind_angle * Constants::pi / 180)) * cos(wind_angle * Constants::pi / 180) + // поворот в сторону направления ветра
				(double(y - y_burn) / 100 - c * sin(wind_angle * Constants::pi / 180)) * sin(wind_angle * Constants::pi / 180);
			double rotated_y = (double(y - y_burn) / 100 - c * sin(wind_angle * Constants::pi / 180)) * cos(wind_angle * Constants::pi / 180) -
				(double(x - x_burn) / 100 - c * cos(wind_angle * Constants::pi / 180)) * sin(wind_angle * Constants::pi / 180);

			if (tiles[y][x]->state == BurnState::not_burned && tiles[y][x]->type == Tile::forest && 
				(pow(rotated_y, 2) / pow(a, 2) + pow(rotated_x, 2) / pow(b, 2)) <= 1) {
				tiles[y][x]->state = BurnState::on_fire;
			}
		}
	}
}