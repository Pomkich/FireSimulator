#include <iostream>
#include <array>
#include "Constants.h"

using namespace std;

void Draw(array<array<Tile, 10>, 10> &tiles) {
	for (auto& row : tiles) {
		for (auto tile : row) {
			cout << static_cast<int>(tile) << " ";
		}
		cout << endl;
	}
}

int main() {
	array<array<Tile, 10>, 10> tiles;
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
			tiles[i][j] = static_cast<Tile>(start_tiles[i][j]);
		}
	}

	Draw(tiles);

	return 0;
}