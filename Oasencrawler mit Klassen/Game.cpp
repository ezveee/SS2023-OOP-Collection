#include <iostream>
#include "Game.h"
#include "GameObjects.h"
#include "Player.h"
#include "Enemy.h"

Game::Game() = default;
Game::~Game() = default;

playfield Game::getWorld() const
{
	return world;
}

int Game::getTotalRelics() const
{
	return this->totalRelics;
}

void Game::fillWorld()
{
	for (int y = 0; y < MAP_SIZE_Y; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X; ++x)
		{
			if (x == PLAYER_START_X && y == PLAYER_START_Y)
			{
				world[x][y] = WorldElement::EmptyField;
				continue;
			}

			if (x == ENEMY_START_X && y == ENEMY_START_Y)
			{
				world[x][y] = WorldElement::EmptyField;
				continue;
			}

			int randomNumber = rand() % 10 + 1;

			if (randomNumber >= 1 && randomNumber <= 4)
				world[x][y] = WorldElement::EmptyField;

			if (randomNumber >= 5 && randomNumber <= 8)
				world[x][y] = WorldElement::DangerField;

			if (randomNumber == 9)
				world[x][y] = WorldElement::FountainField;

			if (randomNumber == 10)
			{
				world[x][y] = WorldElement::RelicField;
				++(this->totalRelics);
			}
		}
	}

	if (this->totalRelics == 0)
	{
		int xPosition;
		int yPosition;
		do
		{
			xPosition = rand() % MAP_SIZE_X;
			yPosition = rand() % MAP_SIZE_Y;

		} while (xPosition == PLAYER_START_X && yPosition == PLAYER_START_Y);

		world[xPosition][yPosition] = WorldElement::RelicField;
		++(this->totalRelics);
	}
}

void Game::printWorld(const Player& player, const Enemy& enemy) const
{
	int realSizeX = MAP_SIZE_X * (SCALE_FACTOR_X + 1) + 1;
	int realSizeY = MAP_SIZE_Y * (SCALE_FACTOR_Y + 1) + 1;

	for (int guiY = 0; guiY < realSizeY; ++guiY)
	{
		for (int guiX = 0; guiX < realSizeX; ++guiX)
		{
			bool isOnGridY = (guiX % (SCALE_FACTOR_X + 1)) == 0;
			bool isOnGridX = (guiY % (SCALE_FACTOR_Y + 1)) == 0;

			if (isOnGridX && isOnGridY)
			{
				std::wcout << CORNER_BORDER;
				continue;
			}

			if (isOnGridX && !isOnGridY)
			{
				std::wcout << HORIZONTAL_BORDER;
				continue;
			}

			if (!isOnGridX && isOnGridY)
			{
				std::wcout << VERTICAL_BORDER;
				continue;
			}

			// calculate if current position is field to represent world content
			bool isWorldContentX = (guiX - (SCALE_FACTOR_X + 1) / 2) % (SCALE_FACTOR_X + 1) == 0;
			bool isWorldContentY = (guiY - (SCALE_FACTOR_Y + 1) / 2) % (SCALE_FACTOR_Y + 1) == 0;

			// otherwise
			if (!isWorldContentX || !isWorldContentY)
			{
				// it's an empty space
				std::wcout << MARGIN_FIELD;
				continue;
			}

			int xPos = guiX / (SCALE_FACTOR_X + 1);
			int yPos = guiY / (SCALE_FACTOR_Y + 1);

			Vector2d playerPosition = player.getPosition();
			Vector2d enemyPosition = enemy.getPosition();

			if (enemyPosition.x == xPos && enemyPosition.y == yPos)
			{
				std::wcout << ENEMY_CHAR;
				continue;
			}

			if (playerPosition.x == xPos && playerPosition.y == yPos)
			{
				std::wcout << PLAYER_CHAR;
				continue;
			}

			std::wcout << (char)this->world[xPos][yPos];
		}
		std::wcout << std::endl;
	}
}

void Game::setWorld(int x, int y, WorldElement newField)
{
	this->world[x][y] = newField;
}
