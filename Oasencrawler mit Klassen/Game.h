#pragma once
#include <array>
#include <iostream>
#include "defines.h"
#include "WorldElement.h"

class Player;
class Enemy;

using playfield = std::array <std::array <WorldElement, MAP_SIZE_Y>, MAP_SIZE_X>;


class Game
{
	public:
		Game();
		virtual ~Game();

		void fillWorld();
		void printWorld(const Player &player, const Enemy &enemy) const;

		int getTotalRelics() const;
		playfield getWorld() const;
		void setWorld(int x, int y, WorldElement newField);

	private:
		playfield world;
		int totalRelics = 0;
		std::string eventLog;
};

