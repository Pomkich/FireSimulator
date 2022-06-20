#pragma once
#include "Constants.h"

enum class Tile {
	empty = 0, water, forest
};

enum class BurnState {
	not_burned, burned, on_fire
};

struct Cell {
	double wind_speed;
	double wind_angle;
	Tile type;
	BurnState state;

	Cell() = default;
	Cell(Tile t) : type(t), state(BurnState::not_burned) {};
};