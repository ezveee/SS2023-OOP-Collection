#include "GameObjects.h"
#include <conio.h>
#include "defines.h"

void GameObjects::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void GameObjects::setPosition(Vector2d newPosition)
{
	this->position.x = newPosition.x;
	this->position.y = newPosition.y;
}

Vector2d GameObjects::getPosition() const
{
	return this->position;
}

void GameObjects::printText(const std::string &outputText) const
{
	for (int i = 0; i < outputText.size(); ++i)
	{
		if (_kbhit()) // check if a key has been pressed
		{
			std::wcout << outputText.substr(i).c_str();
			return;
		}
		std::wcout << outputText[i];
		Sleep(CHARACTER_OUTPUT_SPEED);
	}
}

int GameObjects::normalize(int value) const
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	return 0;
}
