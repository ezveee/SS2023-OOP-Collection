#include "Ship.h"
#include <iostream>
#include <cstdlib>

std::string Ship::getName() const
{
	return name;
}

int Ship::getHull() const
{
	return hull;
}

void Ship::damageHull(int damage)
{
	hull -= damage;
}

int Ship::getSize() const
{
	return size;
}

int Ship::getDamage() const
{
	return damage;
}
