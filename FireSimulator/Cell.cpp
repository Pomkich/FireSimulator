#include "Cell.h"

Cell::Cell() {
	type = Tile::empty;
	damage = 0;
	burning_rate = 0;
}

void Cell::Update() {
	damage += burning_rate;
}