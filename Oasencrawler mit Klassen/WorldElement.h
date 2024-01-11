#pragma once
#include "defines.h"

enum class WorldElement
{
	CornerBorder = CORNER_BORDER,
	HorizontalBorder = HORIZONTAL_BORDER,
	VerticalBorder = VERTICAL_BORDER,
	EmptyField = EMPTY_FIELD,

	DangerField = DANGER_FIELD,
	FountainField = FOUNTAIN_FIELD,
	RelicField = RELIC_FIELD
};
