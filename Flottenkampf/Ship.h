#pragma once

#include "constants.h"
#include <iostream>
#include <string>

class Ship
{
public:
	Ship() = default;
	virtual ~Ship() = default;

	virtual void attack(Ship* opposingShip) = 0;

	std::string getName() const;
	int getHull() const;
	void damageHull(int damage);
	int getSize() const;
	int getDamage() const;

protected:
	std::string name;
	int hull;
	int size;
	int damage;
};

