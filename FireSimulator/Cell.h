#pragma once
#include "Constants.h"

struct Cell {
	Tile type;
	int damage;
	int burning_rate;

	Cell();
	void Update();
};