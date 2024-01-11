// Oasencrawler ohne Klassen.cpp

#include <iostream>
#include <conio.h>

// for unicode characters
#include <fcntl.h>
#include <io.h>
#include <string>


#define MAP_SIZE_X						5
#define MAP_SIZE_Y						5

#define SCALE_FACTOR_X					3
#define SCALE_FACTOR_Y					1


#define ALL_RELICS_FOUND_MESSAGE		"You found all relics!\n"
#define QUIT_GAME_MESSAGE				"You have quit the game\n"
#define PLAYER_RELIC_FOUND_MESSAGE		"You have found a relic.\n"
#define PLAYER_DAMAGE_TAKEN_MESSAGE		"You have taken damage.\n"
#define PLAYER_DAMAGE_DODGED_MESSAGE	"You dodged in time.\n"
#define PLAYER_DIED_MESSAGE				"You have died\n"
#define PLAYER_CAUGHT_MESSAGE			"You have been caught\n"
#define PRESS_TO_CONTINUE_MESSAGE		"Press any key to continue\n"
#define PLAYER_FOUNTAIN_FOUND_MESSAGE	"You have found a fountain!\n"
#define PLAYER_HP_REPLENISHED_MESSAGE	"Replenished 1 HP\n"
#define PLAYER_MAX_HP_MESSAGE			"You are already at max HP\n"
#define LABEL_DAMAGE_ROLL				"Dice roll: "

#define LABEL_HP						"HP:		"
#define LABEL_MOVES						"Moves:		"
#define LABEL_RELICS					"Relics:		"
#define LABEL_RELICS_OUT_OF				"/"
#define LABEL_POSITION_OPEN_BRACKET		"Position:	("
#define LABEL_POSITION_MIDDLE_LINE		"|"
#define LABEL_POSITION_CLOSING_BRACKET	")\n"
#define LABEL_EVENT_HISTORY				"\nEvent history:\n"

#define PLAYER_CHAR						'X'
#define ENEMY_CHAR						'E'
#define PLAYER_HP						L'\u2665' // unicode for heart

#define DANGER_FIELD					'a'
#define FOUNTAIN_FIELD					'b'
#define RELIC_FIELD						'c'

#define PLAYER_START_X					0
#define PLAYER_START_Y					0
#define ENEMY_START_Y					MAP_SIZE_Y - 1
#define ENEMY_START_X					MAP_SIZE_X - 1

#define CORNER_BORDER					'+'
#define HORIZONTAL_BORDER				'-'
#define VERTICAL_BORDER					'|'
#define EMPTY_FIELD						' '
#define MARGIN_FIELD					' '

#define ARROWKEY_UP						72
#define ARROWKEY_DOWN					80
#define ARROWKEY_LEFT					75
#define ARROWKEY_RIGHT					77
#define ESCAPEKEY						27

#define MAX_HEALTH						5

/*
	Enums
*/
typedef enum worldElements
{
	cornerBorder = CORNER_BORDER,
	horizontalBorder = HORIZONTAL_BORDER,
	verticalBorder = VERTICAL_BORDER,
	emptyField = EMPTY_FIELD,

	dangerField = DANGER_FIELD,
	fountainField = FOUNTAIN_FIELD,
	relicField = RELIC_FIELD

} worldElements;


typedef enum userInput
{
	moveUp,
	moveDown,
	moveLeft,
	moveRight,
	endGame,
	invalid

} userInput;


/*
	Structs
*/
typedef struct coordinate
{
	int x;
	int y;

} coordinate;

typedef struct player
{
	coordinate position;
	int health;
	int moves;
	int relics;

} player;

typedef struct enemy
{
	coordinate position;

} enemy;

typedef struct game
{
	worldElements world[MAP_SIZE_X][MAP_SIZE_Y];
	player playerA;
	enemy enemyA;
	std::string events;

} game;


/*
	Forward declarations
*/
// INITIALIZATION
void initializeGame(game* myGame);
void fillWorld(worldElements world[MAP_SIZE_X][MAP_SIZE_Y], int* totalRelics);
void setGameObjects(game* myGame);

// CHECK
std::string checkField(game* myGame);

// PRINT
void printStats(game myGame, int totalRelics);
void printWorld(game myGame);
void printStatusText(std::string statusText);
void printEvents(game myGame);

// MOVEMENT
userInput getUserInput();
void processMovement(game* myGame, userInput input, bool* isExitRequestedPtr);
void moveEnemy(enemy* myEnemy, player myPlayer);


/*
	Main
*/
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // to print out unicode characters

	// get system time for seed
	srand(time(0));

	game* myGame = new game;
	initializeGame(myGame);

	int totalRelics = 0;
	int* totalRelicsPtr = &totalRelics;

	fillWorld(myGame->world, totalRelicsPtr);
	setGameObjects(myGame);

	bool isExitRequested = false;
	bool* isExitRequestedPtr = &isExitRequested;

	while (true)
	{
		system("CLS");

		std::string statusText = checkField(myGame);

		printStats(*myGame, totalRelics);

		printWorld(*myGame);

		printStatusText(statusText);
		
		myGame->world[myGame->playerA.position.x][myGame->playerA.position.y] = emptyField;
		// set field to empty after player has been on it

		if (isExitRequested)
		{
			std::wcout << QUIT_GAME_MESSAGE;
			break;
		}

		if (myGame->playerA.relics == totalRelics)
		{
			std::wcout << ALL_RELICS_FOUND_MESSAGE;
			break;
		}

		if (myGame->playerA.health <= 0)
		{
			std::wcout << PLAYER_DIED_MESSAGE;
			break;
		}

		if (myGame->playerA.position.x == myGame->enemyA.position.x &&
			myGame->playerA.position.y == myGame->enemyA.position.y)
		{
			std::wcout << PLAYER_CAUGHT_MESSAGE;
			break;
		}

		userInput input = getUserInput();

		processMovement(myGame, input, isExitRequestedPtr);

	}

	printEvents(*myGame);

	delete myGame;

}


userInput getUserInput()
{
	char input = _getch(); // for input without having to press enter

	switch (input)
	{
		case 'w':
		case 'W':
		case ARROWKEY_UP:
			return moveUp;

		case 'a':
		case 'A':
		case ARROWKEY_LEFT:
			return moveLeft;

		case 's':
		case 'S':
		case ARROWKEY_DOWN:
			return moveDown;

		case 'd':
		case 'D':
		case ARROWKEY_RIGHT:
			return moveRight;

		case 'q':
		case 'Q':
		case ESCAPEKEY:
			return endGame;

		default:
			return invalid;
	}
}


/*
	Functions
*/
void initializeGame(game* myGame)
{
	myGame->playerA.health = MAX_HEALTH;
	myGame->playerA.moves = 0;
	myGame->playerA.relics = 0;
}

void fillWorld(worldElements world[MAP_SIZE_X][MAP_SIZE_Y], int* totalRelicsPtr)
{
	for (int y = 0; y < MAP_SIZE_Y; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X; ++x)
		{
			if (x == PLAYER_START_X && y == PLAYER_START_Y)
			{
				world[x][y] = emptyField;
				continue;
			}

			if (x == ENEMY_START_X && y == ENEMY_START_Y)
			{
				world[x][y] = emptyField;
				continue;
			}

			int randomNumber = rand() % 10 + 1;

			if (randomNumber >= 1 && randomNumber <= 4)
				world[x][y] = emptyField;

			if (randomNumber >= 5 && randomNumber <= 8)
				world[x][y] = dangerField;

			if (randomNumber == 9)
				world[x][y] = fountainField;

			if (randomNumber == 10)
			{
				world[x][y] = relicField;
				++(*totalRelicsPtr);
			}
		}
	}

	if (*totalRelicsPtr == 0)
	{
		int xPosition;
		int yPosition;
		do
		{
			xPosition = rand() % MAP_SIZE_X;
			yPosition = rand() % MAP_SIZE_Y;

		} while (xPosition == PLAYER_START_X && yPosition == PLAYER_START_Y);

		world[xPosition][yPosition] = relicField;
		++(*totalRelicsPtr);
	}
}

void setGameObjects(game* myGame)
{
	myGame->playerA.position.x = PLAYER_START_X;
	myGame->playerA.position.y = PLAYER_START_Y;

	myGame->enemyA.position.x = ENEMY_START_X;
	myGame->enemyA.position.y = ENEMY_START_Y;
}

std::string checkField(game* myGame)
{
	
	int damageProbability;
	std::string statusText = "";
	
	if (myGame->playerA.position.x == myGame->enemyA.position.x &&
		myGame->playerA.position.y == myGame->enemyA.position.y)
	{
		return statusText;
	}

	switch (myGame->world[myGame->playerA.position.x][myGame->playerA.position.y])
	{
	case dangerField:
		damageProbability = rand() % 6 + 1;
		//damageProbability = 6;

		statusText.append(LABEL_DAMAGE_ROLL); // append to add text at end of string
		statusText.append(std::to_string(damageProbability)); // convert int to string
		statusText.append("\n");

		if (damageProbability == 6)
		{
			--(myGame->playerA.health);
			statusText.append(PLAYER_DAMAGE_TAKEN_MESSAGE);
		}
		else
		{
			statusText.append(PLAYER_DAMAGE_DODGED_MESSAGE);
		}
		break;

	case fountainField:
		statusText.append(PLAYER_FOUNTAIN_FOUND_MESSAGE);
		if (myGame->playerA.health < MAX_HEALTH)
		{
			++(myGame->playerA.health);
			statusText.append(PLAYER_HP_REPLENISHED_MESSAGE);
		}
		else
		{
			statusText.append(PLAYER_MAX_HP_MESSAGE);
		}
		break;

	case relicField:
		++(myGame->playerA.relics);
		statusText.append(PLAYER_RELIC_FOUND_MESSAGE);
		break;

	default:
		break;
	}
	myGame->events.append(statusText);
	return statusText;
}

void printStats(game myGame, int totalRelics)
{
	std::wcout << LABEL_HP; // use wcout to display wide characters
	for (int i = 0; i < myGame.playerA.health; ++i)
		std::wcout << PLAYER_HP;
	std::wcout << "\n";

	std::wcout << LABEL_MOVES << myGame.playerA.moves << "\n";

	std::wcout << LABEL_RELICS << myGame.playerA.relics << LABEL_RELICS_OUT_OF << totalRelics << "\n";
	std::wcout << LABEL_POSITION_OPEN_BRACKET << myGame.playerA.position.x
			   << LABEL_POSITION_MIDDLE_LINE << myGame.playerA.position.y
			   << LABEL_POSITION_CLOSING_BRACKET;
}

void printStatusText(std::string statusText)
{
	if (statusText == "")
	{
		return;
	}
	std::wcout << statusText.c_str(); // .c_str() for wcout compability
	std::wcout << PRESS_TO_CONTINUE_MESSAGE;
	_getch();
}

void printEvents(game myGame)
{
	if (myGame.events == "")
	{
		return;
	}
	std::wcout << LABEL_EVENT_HISTORY;
	std::wcout << myGame.events.c_str();
}


void printWorld(game myGame)
{
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

			if (myGame.playerA.position.x == xPos && myGame.playerA.position.y == yPos)
			{
				std::wcout << PLAYER_CHAR;
				continue;
			}

			if (myGame.enemyA.position.x == xPos && myGame.enemyA.position.y == yPos)
			{
				std::wcout << ENEMY_CHAR;
				continue;
			}

			std::wcout << (char)myGame.world[xPos][yPos];
		}
		std::wcout << std::endl;
	}
}

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

void processMovement(game* myGame, userInput input, bool* isExitRequestedPtr)
{
	int deltaX = 0;
	int deltaY = 0;

	switch (input)
	{
	case moveUp:
		deltaY = -1;
		break;

	case moveLeft:
		deltaX = -1;
		break;

	case moveDown:
		deltaY = 1;
		break;

	case moveRight:
		deltaX = 1;
		break;

	case endGame:
		*isExitRequestedPtr = true;
		return;

	default:
		return;
	}

	int newX = myGame->playerA.position.x + deltaX;
	int newY = myGame->playerA.position.y + deltaY;

	if (newX >= 0 && newX < MAP_SIZE_X && newY >= 0 && newY < MAP_SIZE_Y)
	{
		myGame->playerA.position.x = newX;
		myGame->playerA.position.y = newY;

		++(myGame->playerA.moves);
		if (myGame->playerA.moves % 2 == 0)
		{
			moveEnemy(&(myGame->enemyA), myGame->playerA);
		}
	}
}

void moveEnemy(enemy* myEnemy, player myPlayer)
{
	if (myPlayer.position.y < myEnemy->position.y)
	{
		--(myEnemy->position.y);
		return;
	}
	if (myPlayer.position.y > myEnemy->position.y)
	{
		++(myEnemy->position.y);
		return;
	}
	if (myPlayer.position.x < myEnemy->position.x)
	{
		--(myEnemy->position.x);
		return;
	}
	if (myPlayer.position.x > myEnemy->position.x)
	{
		++(myEnemy->position.x);
		return;
	}
}
