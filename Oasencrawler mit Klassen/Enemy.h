#pragma once
#include "GameObjects.h"

class Enemy : public GameObjects
{
	public:
		Enemy();
		virtual ~Enemy();

		void moveEnemy(const Vector2d &playerPosition);
};

