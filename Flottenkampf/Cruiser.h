#pragma once

#include "Ship.h"

class Cruiser : public Ship
{
public:
	Cruiser();
	virtual ~Cruiser() = default;

	void attack(Ship* opposingShip) override;
};

