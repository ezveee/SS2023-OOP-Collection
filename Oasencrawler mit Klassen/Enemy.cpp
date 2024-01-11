#include <math.h>
#include "defines.h"
#include "Enemy.h"

Enemy::Enemy()
{
	this->setPosition(ENEMY_START_X, ENEMY_START_Y);
}

Enemy::~Enemy() = default;

void Enemy::moveEnemy(const Vector2d &playerPosition)
{
	Vector2d enemyPosition = getPosition();

	// Calculate distance between current enemy position and player position.
	int xDiff = playerPosition.x - enemyPosition.x;
	int yDiff = playerPosition.y - enemyPosition.y;

	// Reduce greatest axis-distance at first.
	if (abs(xDiff) > abs(yDiff))
	{
		setPosition(enemyPosition.x + normalize(xDiff), enemyPosition.y);
	}
	else
	{
		setPosition(enemyPosition.x, enemyPosition.y + normalize(yDiff));
	}
}
