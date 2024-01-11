// Flottenkampf.cpp

#include <iostream>
#include "Game.h"

//#define DEBUG

#ifdef DEBUG

#include "Cruiser.h"
#include "Destroyer.h"
#include "Hunter.h"

#endif // DEBUG

int main()
{
	srand(time(nullptr));

	Game game;
	game.run();

	#ifdef DEBUG
	auto hunter = new Hunter();
	std::cout << "Hull: " << hunter->hull << "\n";
	std::cout << "Size: " << hunter->size << "\n";
	std::cout << "Damage: " << hunter->damage << "\n";
	#endif // DEBUG
}

