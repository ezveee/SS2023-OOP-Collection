#pragma once

#include <vector>
#include <iostream>
#include "constants.h"
#include "Fleet.h"

class Game
{
public:
	void run();
	void assembleFleet(Fleet& fleet);

private:
	void selectShip(Fleet& fleet);
	Ship* createShip(char input);
	void displayShipSelectionUI() const;
	bool isNewShipPossible(const Fleet& fleet) const;
	char getSelectionInput(int fleetSize) const;
	bool isInputValid(char input, int fleetSize) const;
	bool isGameOver() const;


	bool isExitRequested = false;
	Fleet playerFleet;
	Fleet opposingFleet;
};

