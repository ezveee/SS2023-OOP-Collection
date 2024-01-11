#include "Destroyer.h"

Destroyer::Destroyer()
{
	name = "Destroyer";
	hull = DESTROYER_HULL;
	size = DESTROYER_SIZE;
	damage = DESTROYER_DAMAGE;
}

void Destroyer::attack(Ship* opposingShip)
{
	#ifdef DEBUG
	int diceRoll = 10;
	#else
	int diceRoll = rand() % 10 + 1;
	#endif

	std::cout << "DiceRoll: " << diceRoll << "\n";

	if (diceRoll >= opposingShip->getSize() - 2)
	{
		std::cout << "Attack successful!" << "\n";
		opposingShip->damageHull(this->damage);
		return;
	}

	std::cout << "Attack failed." << "\n";

}
