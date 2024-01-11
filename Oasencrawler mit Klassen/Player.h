#pragma once
#include <Windows.h>

#include "Vector2d.h"
#include "UserInput.h"
#include "GameObjects.h"

class Game;
class Enemy;


class Player : public GameObjects
{
	public:
		Player();
		virtual ~Player();

		int getHealth() const;
		void incrementHealth();
		void decrementHealth();

		int getMoveCounter() const;
		void incrementMoveCounter();

		int getRelicCounter() const;
		void incrementRelicCounter();

		bool getIsExitRequested() const;

		void printStats(const Game &game) const;

		void processMovement(UserInput input);

		std::string checkField(const Vector2d& enemyPosition, const Game& game);

		void printStatusText(const std::string &statusText/*, HANDLE console, WORD defaultAttributes, COORD startPos*/) const;

		void printEventLog() const;

	private:
		int health = MAX_HEALTH;
		int moveCounter = 0;
		int relicCounter = 0;

		std::string eventLog;
		bool isExitRequested = false;

		void setHealth(int health);
};
