#include <iostream>
#include <array>
#include "Constants.h"
#include "Cell.h"

using namespace std;

int main() {
	array<array<Cell, 10>, 10> tiles;
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

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tiles[i][j] = Cell(static_cast<Tile>(start_tiles[i][j]));
		}
	}

	for (int i = 0; i < 10; i++) {
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
	}

	return 0;
}