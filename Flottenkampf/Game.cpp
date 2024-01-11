#include "Game.h"
#include "Hunter.h"
#include "Destroyer.h"
#include "Cruiser.h"
#include "conio.h"
#include <stdexcept>

//#define DEBUG

void pressAnyKey();

void Game::run()
{
	// assemble fleets
	displayShipSelectionUI();
	std::cout << "\nAssemble Player Fleet:\n";
	assembleFleet(playerFleet);
	pressAnyKey();

	displayShipSelectionUI();
	std::cout << "\nAssemble Opposing Fleet:\n";
	assembleFleet(opposingFleet);
	pressAnyKey();

	// fight
	int turnCounter = 0;
	bool isPlayerTurn;

	while (!isGameOver())
	{
		isPlayerTurn = (turnCounter % 2 == 0);

		int randomPlayerShip = rand() % playerFleet.ships.size();
		int randomOpposingShip = rand() % opposingFleet.ships.size();

		std::cout << "------------------- Round " << turnCounter + 1 << " -------------------\n";

		if (isPlayerTurn)
		{
			std::cout << "Player's turn\n";
			std::cout << playerFleet.ships[randomPlayerShip]->getName()
				<< " attacks " << opposingFleet.ships[randomOpposingShip]->getName() << "\n";

			playerFleet.ships[randomPlayerShip]->attack(opposingFleet.ships[randomOpposingShip]);

			if (opposingFleet.ships[randomOpposingShip]->getHull() < 0)
			{
				std::cout << "Ship destroyed!\n";
				opposingFleet.ships.erase(std::remove(opposingFleet.ships.begin(), opposingFleet.ships.end(), opposingFleet.ships[randomOpposingShip]), opposingFleet.ships.end());
			}
		}
		else
		{
			std::cout << "Opponent's turn\n";
			std::cout << opposingFleet.ships[randomOpposingShip]->getName()
				<< " attacks " << playerFleet.ships[randomPlayerShip]->getName() << "\n";

			opposingFleet.ships[randomOpposingShip]->attack(playerFleet.ships[randomPlayerShip]);

			if (playerFleet.ships[randomPlayerShip]->getHull() < 0)
			{
				std::cout << "Ship destroyed!\n";
				playerFleet.ships.erase(std::remove(playerFleet.ships.begin(), playerFleet.ships.end(), playerFleet.ships[randomPlayerShip]), playerFleet.ships.end());
		}

	}

		#ifdef DEBUG
		std::cout << "Hull attackedShip: " << attackedShip->getHull() << "\n";
		#endif // DEBUG

		std::cout << "-----------------------------------------------";
		if (turnCounter >= 10)
			std::cout << "-";
		std::cout << "\n";

		++turnCounter;
	}
}

void Game::assembleFleet(Fleet& fleet)
{
	selectShip(fleet);

	std::cout << "\n";
	for (auto ship : fleet.ships)
	{
		std::cout << ship->getName() << " ("
			<< ship->getHull() << ", "
			<< ship->getSize() << ", "
			<< ship->getDamage() << ")\n";
	}
}

void Game::selectShip(Fleet& fleet)
{
	char input;
	do
	{
		if (!isNewShipPossible(fleet))
		{
			std::cout << "No more ships can be added.\n";
			return;
		}

		input = getSelectionInput(fleet.fleetSize);
		auto newShip = createShip(input);

		if (newShip != nullptr)
		{
			int newSize = fleet.fleetSize + newShip->getSize();
			if (newSize <= MAX_FLEET_SIZE)
			{
				fleet.ships.push_back(newShip);
				fleet.fleetSize = newSize;
				std::cout << "Fleet size: " << fleet.fleetSize << "/" << MAX_FLEET_SIZE << "\n";
			}
			else
			{
				delete newShip;
				std::cout << "Ship too big.\n";
			}
		}

	} while (input != SELECTION_EXIT_KEY);
}

char Game::getSelectionInput(int fleetSize) const
{
	char input;
	do
	{
		std::cin >> input;
	} while (!isInputValid(input, fleetSize));

	return input;
}

bool Game::isInputValid(char input, int fleetSize) const
{
	switch (input)
	{
	case 'h':
	case 'd':
	case 'c':
		return true;

	case 'q':
		if (fleetSize > 0)
			return true;

		std::cout << "Fleet cannot consist of 0 ships.\n";
		return false;

	default:
		return false;
	}
}

Ship* Game::createShip(char input)
{
	switch (input)
	{
	case 'h':
		return new Hunter();

	case 'd':
		return new Destroyer();

	case 'c':
		return new Cruiser();

	case 'q':
		return nullptr;

	default:
		std::cout << "Input invalid.\n";
		return nullptr;
	}
}

void Game::displayShipSelectionUI() const
{
	std::cout << "Please select a ship-type. (q: end selection early)\n";
	std::cout << "\tkey: Ship-Type\t(hull, size, damage)\n";
	std::cout << "\th: Hunter\t("
		<< HUNTER_HULL << ", "
		<< HUNTER_SIZE << ", "
		<< HUNTER_DAMAGE << ")"
		<< "\n";

	std::cout << "\td: Destroyer\t("
		<< DESTROYER_HULL << ", "
		<< DESTROYER_SIZE << ", "
		<< DESTROYER_DAMAGE << ")"
		<< "\n";

	std::cout << "\tc: Cruiser\t("
		<< CRUISER_HULL << ", "
		<< CRUISER_SIZE << ", "
		<< CRUISER_DAMAGE << ")"
		<< "\n";

}

bool Game::isNewShipPossible(const Fleet& fleet) const
{
	return (fleet.fleetSize + HUNTER_SIZE) <= MAX_FLEET_SIZE ||
		(fleet.fleetSize + DESTROYER_SIZE) <= MAX_FLEET_SIZE ||
		(fleet.fleetSize + CRUISER_SIZE) <= MAX_FLEET_SIZE;
}

bool Game::isGameOver() const
{
	if (playerFleet.ships.empty())
	{
		std::cout << "\nYou have lost.\n";
		return true;
	}

	if (opposingFleet.ships.empty())
	{
		std::cout << "\nYou have won!\n";
		return true;
	}

	return false;
}

void pressAnyKey()
{
	std::cout << "\nPress any key to continue.\n";
	_getch();
	system("CLS");
}
