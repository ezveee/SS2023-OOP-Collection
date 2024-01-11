// Oasencrawler ohne Klassen.cpp

#include <Windows.h>
#include <iostream>
#include <conio.h>

// for unicode characters
#include <fcntl.h>
#include <io.h>
#include <string>

#include "defines.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"


/*
	Forward declarations
*/
UserInput getUserInput();

/*
	Main
*/
int main()
{
	(void)_setmode(_fileno(stdout), _O_U16TEXT); // to print out unicode characters

	// get system time for seed
	srand((unsigned int)time(nullptr));

	bool isToBeContinued = true;

	Game game;
	Player player;
	Enemy enemy;

	game.fillWorld();

	while (isToBeContinued)
	{
		Vector2d playerPosition = player.getPosition();
		Vector2d enemyPosition = enemy.getPosition();
		
		system("CLS");

		std::string statusText = player.checkField(enemyPosition, game);

		player.printStats(game);

		game.printWorld(player, enemy);

		player.printStatusText(statusText);

		game.setWorld(playerPosition.x, playerPosition.y, WorldElement::EmptyField);

		if (player.getIsExitRequested())
		{
			player.printText(QUIT_GAME_MESSAGE);
			isToBeContinued = false;
			continue;
		}

		if (player.getRelicCounter() == game.getTotalRelics())
		{
			player.printText(ALL_RELICS_FOUND_MESSAGE);
			isToBeContinued = false;
			continue;
		}

		if (player.getHealth() <= 0)
		{
			player.printText(PLAYER_DIED_MESSAGE);
			isToBeContinued = false;
			continue;
		}

		if (playerPosition.x == enemyPosition.x &&
			playerPosition.y == enemyPosition.y)
		{
			player.printText(PLAYER_CAUGHT_MESSAGE);
			isToBeContinued = false;
			continue;
		}

		UserInput input;
		do
		{
			input = getUserInput();

		} while (input == UserInput::Invalid);

		player.processMovement(input);

		// Enemy moves only every second player step
		if (player.getMoveCounter() % 2 == 0)
		{
			enemy.moveEnemy(player.getPosition());
		}
	}

	player.printEventLog();

	/*

	// colorful text output
	// NOT WORKING YET
	// printStatusText function !!!

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	WORD defaultAttributes = consoleInfo.wAttributes;

	COORD startPos = consoleInfo.dwCursorPosition;
	startPos.X = 0;

	*/

}


/*
	Functions
*/
UserInput getUserInput()
{
	char input = _getch(); // for input without having to press enter

	switch (input)
	{
	case 'w':
	case 'W':
	case ARROWKEY_UP:
		return UserInput::MoveUp;

	case 'a':
	case 'A':
	case ARROWKEY_LEFT:
		return UserInput::MoveLeft;

	case 's':
	case 'S':
	case ARROWKEY_DOWN:
		return UserInput::MoveDown;

	case 'd':
	case 'D':
	case ARROWKEY_RIGHT:
		return UserInput::MoveRight;

	case 'q':
	case 'Q':
	case ESCAPEKEY:
		return UserInput::EndGame;

	default:
		return UserInput::Invalid;
	}
}

// GRID
// ====
//
// Size / Scale
//   5  /   1    -> 11
//   5  /   2    -> 16
//   5  /   3    -> 21
//
//   4  /   1    -> 9
//   4  /   2    -> 13
//   4  /   3    -> 17
//
// Size * (Scale + 1) + 1
	
/*
Scale: 1
+-+-+-+-+-+
|A|B|C|D|E| -> 1, 3, 5, 7, 9 (+2)
+-+-+-+-+-+

Scale: 2
+--+--+--+--+--+
|A |B |C |D |E | -> 1, 4, 7, 10, 13 (+3)
+--+--+--+--+--+

Scale: 3
+---+---+---+---+---+
| A | B | C | D | E | -> 2, 6, 10, 14, 18
+---+---+---+---+---+

Scale: 4
+----+----+----+----+----+
|    |    |    |    |    |
| A  | B  | C  | D  | E  | -> 2, 7, 12, 17, 22
|    |    |    |    |    |
+----+----+----+----+----+

Scale: 5
+-----+-----+-----+-----+-----+
|  A  |  B  |  C  |  D  |  E  | -> 3, 9, 15, 21, 27
+-----+-----+-----+-----+-----+

Scale: 6
+------+------+------+------+------+
|  A   |  B   |  C   |  D   |  E   | -> 3, 10, 17, 24, 31
+------+------+------+------+------+

Scale: 7
+-------+-------+-------+-------+-------+
|   A   |   B   |   C   |   D   |   E   | -> 4, 12, 20, 28, 36
+-------+-------+-------+-------+-------+

*/
