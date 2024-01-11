#include <iostream>
#include <string>
#include <conio.h>

#include "defines.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	setPosition(PLAYER_START_X, PLAYER_START_Y);
}

Player::~Player() = default;

int Player::getHealth() const
{
	return this->health;
}

void Player::incrementHealth()
{
	++(this->health);
}

void Player::decrementHealth()
{
	--(this->health);
}

int Player::getMoveCounter() const
{
	return this->moveCounter;
}

void Player::incrementMoveCounter()
{
	++(this->moveCounter);
}

int Player::getRelicCounter() const
{
	return this->relicCounter;
}

void Player::incrementRelicCounter()
{
	++(this->relicCounter);
}

void Player::printStats(const Game &game) const
{
	std::wcout << LABEL_HP; // use wcout to display wide characters
	for (int i = 0; i < this->health; ++i)
		std::wcout << PLAYER_HP;
	std::wcout << "\n";

	std::wcout << LABEL_MOVES << this->moveCounter << "\n";

	std::wcout << LABEL_RELICS << this->relicCounter << LABEL_RELICS_OUT_OF
			   << game.getTotalRelics() << "\n";
	std::wcout << LABEL_POSITION_OPEN_BRACKET << this->getPosition().x
			   << LABEL_POSITION_MIDDLE_LINE << this->getPosition().y
			   << LABEL_POSITION_CLOSING_BRACKET;
}

void Player::processMovement(UserInput input)
{
	int deltaX = 0;
	int deltaY = 0;

	switch (input)
	{
	case UserInput::MoveUp:
		deltaY = -1;
		break;

	case UserInput::MoveLeft:
		deltaX = -1;
		break;

	case UserInput::MoveDown:
		deltaY = 1;
		break;

	case UserInput::MoveRight:
		deltaX = 1;
		break;

	case UserInput::EndGame:
		this->isExitRequested = true;
		return;

	default:
		return;
	}

	int newX = this->getPosition().x + deltaX;
	int newY = this->getPosition().y + deltaY;

	if (newX >= 0 && newX < MAP_SIZE_X && newY >= 0 && newY < MAP_SIZE_Y)
	{
		this->setPosition(newX, newY);
		++(this->moveCounter);
	}
}

void Player::setHealth(int healthPoints)
{
	this->health = healthPoints;
}

bool Player::getIsExitRequested() const
{
	return this->isExitRequested;
}

std::string Player::checkField(const Vector2d &enemyPosition, const Game &game)
{

	int damageProbability;
	std::string statusText = "";

	if (this->getPosition().x == enemyPosition.x &&
		this->getPosition().y == enemyPosition.y)
	{
		return statusText;
	}

	playfield world = game.getWorld();

	switch (world[this->getPosition().x][this->getPosition().y])
	{
	case WorldElement::DangerField:
		damageProbability = rand() % 6 + 1;
		//damageProbability = 6;

		statusText.append(LABEL_DAMAGE_ROLL); // append to add text at end of string
		statusText.append(std::to_string(damageProbability)); // convert int to string
		statusText.append("\n");

		if (damageProbability == 6)
		{
			--(this->health);
			statusText.append(PLAYER_DAMAGE_TAKEN_MESSAGE);
		}
		else
		{
			statusText.append(PLAYER_DAMAGE_DODGED_MESSAGE);
		}
		break;

	case WorldElement::FountainField:
		statusText.append(PLAYER_FOUNTAIN_FOUND_MESSAGE);
		if (this->health < MAX_HEALTH)
		{
			++(this->health);
			statusText.append(PLAYER_HP_REPLENISHED_MESSAGE);
		}
		else
		{
			statusText.append(PLAYER_MAX_HP_MESSAGE);
		}
		break;

	case WorldElement::RelicField:
		++(this->relicCounter);
		statusText.append(PLAYER_RELIC_FOUND_MESSAGE);
		break;

	default:
		break;
	}
	this->eventLog.append(statusText);
	return statusText;
}

void Player::printStatusText(const std::string &statusText/*, HANDLE console, WORD defaultAttributes, COORD startPos*/) const
{
	if (statusText == "")
	{
		return;
	}

	this->printText(statusText.c_str()); // .c_str() for wcout compability

	//std::wcout << PRESS_TO_CONTINUE_MESSAGE;
	(void)_getch();

	/*
		NOT WORKING YET
		===============

		cursor position keeps getting set to first line in console
		if i skip printText status text output ->
		blinking gets skipped immediately as well

		===============


	while (!_kbhit())
	{
		SetConsoleCursorPosition(console, startPos);
		SetConsoleTextAttribute(console, BACKGROUND_BLUE);
		std::wcout << "Blinking text" << std::flush;
		Sleep(500);
		SetConsoleCursorPosition(console, startPos);
		SetConsoleTextAttribute(console, defaultAttributes);
		std::wcout << "Blinking text" << std::flush;
		Sleep(500);
	}

	SetConsoleTextAttribute(console, defaultAttributes);
	*/

}

void Player::printEventLog() const
{
	if (this->eventLog == "")
	{
		return;
	}
	this->printText(LABEL_EVENT_HISTORY);
	this->printText((this->eventLog).c_str());
}
