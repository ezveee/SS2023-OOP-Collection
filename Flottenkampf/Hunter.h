#pragma once

#include "Ship.h"

class Hunter : public Ship
{
public:
	Hunter();
	virtual ~Hunter() = default;

	void attack(Ship* opposingShip) override;
};

