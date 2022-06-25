#pragma once
#include <vector>
#include <memory>
#include "Cell.h"

namespace Constants {
	const double pi = 3.14159265;
	const int mesh_size = 300;

	// константы, необходимые для расчёта скорости распространения фронта пожара
	// на данный момент соответстуют местности с кодом 303 (лишайники, сосновый 
	// лес редкий, деревья молодые и средневозрастные)
	const double fuel_load = 1.7;			// w0
	const double fuel_depth = 0.12;			// delta
	const double stv_ratio = 2000;			// sigma
	const double particle_dens = 300;		// p

	const double B = 0.0133 * pow(stv_ratio, 0.54);
	const double C = 7.47 * exp(-0.0693 * pow(stv_ratio, 0.55));
	const double E = 0.715 * exp(-0.0001079 * stv_ratio);

	const double packing_ratio = fuel_load / fuel_depth / particle_dens;	// beta
	const double opm_packing_ratio = 3.348 * pow(stv_ratio, -0.8189);		// beta op
}

void calculateFront(std::vector<std::vector<std::shared_ptr<Cell>>>& tiles, int x_burn, int y_burn);