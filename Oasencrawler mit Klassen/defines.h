#pragma once

#define MAP_SIZE_X						5
#define MAP_SIZE_Y						5

#define SCALE_FACTOR_X					3
#define SCALE_FACTOR_Y					1

#define ALL_RELICS_FOUND_MESSAGE		"* You found all relics.\n"
#define QUIT_GAME_MESSAGE				"* You have quit the game\n"
#define PLAYER_RELIC_FOUND_MESSAGE		"* You have found a relic.\n"
#define PLAYER_DAMAGE_TAKEN_MESSAGE		"* You have taken damage.\n"
#define PLAYER_DAMAGE_DODGED_MESSAGE	"* You dodged in time.\n"
#define PLAYER_DIED_MESSAGE				"* You have died\n"
#define PLAYER_CAUGHT_MESSAGE			"* You have been caught\n"
#define PRESS_TO_CONTINUE_MESSAGE		"* Press any key to continue\n"
#define PLAYER_FOUNTAIN_FOUND_MESSAGE	"* You have found a fountain!\n"
#define PLAYER_HP_REPLENISHED_MESSAGE	"* Replenished 1 HP\n"
#define PLAYER_MAX_HP_MESSAGE			"* You are already at max HP\n"
#define LABEL_DAMAGE_ROLL				"* Dice roll: "

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

#define CHARACTER_OUTPUT_SPEED			20