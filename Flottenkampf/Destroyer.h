#pragma once

#include "Ship.h"

class Destroyer : public Ship
{
public:
	Destroyer();
	virtual ~Destroyer() = default;

	void attack(Ship* opposingShip) override;
};

