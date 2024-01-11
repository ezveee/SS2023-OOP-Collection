#include "Hunter.h"

Hunter::Hunter()
{
	name = "Hunter";
	hull = HUNTER_HULL;
	size = HUNTER_SIZE;
	damage = HUNTER_DAMAGE;
}

void Hunter::attack(Ship* opposingShip)
{
	int diceRoll = rand() % 10 + 1;

	// DEBUG
	// int diceRoll = 10;
	std::cout << "DiceRoll: " << diceRoll << "\n";

	if (diceRoll >= opposingShip->getSize())
	{
		std::cout << "Attack successful!" << "\n";
		if (diceRoll == 9 || diceRoll == 10)
		{
			std::cout << "Critical Strike! :D" << "\n";
			opposingShip->damageHull(2 * this->damage);
			return;
		}
		opposingShip->damageHull(this->damage);
		return;
	}

	std::cout << "Attack failed." << "\n";

}
