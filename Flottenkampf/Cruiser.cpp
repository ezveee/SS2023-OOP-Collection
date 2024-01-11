#include "Cruiser.h"

Cruiser::Cruiser()
{
	name = "Cruiser";
	hull = CRUISER_HULL;
	size = CRUISER_SIZE;
	damage = CRUISER_DAMAGE;
}

void Cruiser::attack(Ship* opposingShip)
{
	bool wasAttackSuccessful = false;
	
	do
	{
		int diceRoll = rand() % 10 + 1;
		std::cout << "DiceRoll: " << diceRoll << "\n";

		if (diceRoll >= opposingShip->getSize())
		{
			wasAttackSuccessful = true;
			opposingShip->damageHull(this->damage);

			if (opposingShip->getHull() < 0)
			{
				return;
			}

			std::cout << "Attack successful! Preparing next attack...\n";
			continue;
		}

		wasAttackSuccessful = false;
		std::cout << "Attack failed." << "\n";

	} while (wasAttackSuccessful);
}
