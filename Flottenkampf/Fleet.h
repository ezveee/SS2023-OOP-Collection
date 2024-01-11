#pragma once

#include "Ship.h"
#include <vector>

struct Fleet
{
	std::vector<Ship*> ships;
	int fleetSize = 0;
};

