#include <iostream>
#include <array>
#include "Constants.h"
#include "Cell.h"

using namespace std;

/*
river and forest with empty fields
int start_tiles[10][10] = {
		{0, 0, 0, 1, 1, 2, 2, 2, 2, 2},
		{0, 0, 0, 1, 1, 2, 2, 2, 2, 2},
		{0, 0, 1, 1, 1, 2, 2, 2, 2, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 0, 0},
		{0, 0, 0, 1, 1, 2, 2, 2, 2, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 2, 2},
		{0, 0, 0, 0, 1, 1, 2, 2, 2, 2},
		{0, 0, 0, 1, 1, 2, 0, 2, 2, 2},
		{0, 0, 1, 1, 0, 2, 0, 0, 2, 2},
		{0, 0, 0, 1, 1, 2, 2, 0, 2, 2},
	};

*/

/*
river and forest with empty fields
int start_tiles[10][10] = {
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	};

*/

void calculateFront(array<array<Cell, 20>, 20> tiles) {
	int x_burn, y_burn;
	double a, b, c;
	double omega = 1.7;	// area code 303
	double wind_speed = 10;	// �������� ����� �/�
	double LB, HB;	// ���������, �������������� ��� ������ ����� �������
	x_burn = 10;	// ��������� ���������� ����� �������
	y_burn = 10;

	LB = 0.936 * exp(0.2566 * wind_speed) + 0.461 * exp(-0.1548 * wind_speed) - 0.397;
	HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));

	b = (omega / 2) * ((1 + HB) / HB);
	a = b / LB;
	c = b - (omega / LB);

	cout << LB << "   " << HB << endl;
	cout << a << "   " << b << "   " << c << endl;

	//a = 2;
	//b = 6;
	/*for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if ((pow(i - x_burn, 2) / pow(a, 2) + pow(j - y_burn, 2) / pow(b, 2)) <= 1) {
				tiles[i][j].state = BurnState::on_fire;
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			cout << static_cast<int>(tiles[i][j].state) << " ";
		}
		cout << endl;
	}*/
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

	/*for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << static_cast<int>(tiles[i][j].type) << " ";
		}
		cout << endl;
	}
	cout << "============================" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << static_cast<int>(tiles[i][j].state) << " ";
		}
		cout << endl;
	}*/

	calculateFront(tiles);

	return 0;
}