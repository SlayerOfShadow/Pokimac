#include "Case.h"

Case::Case(int x, char c, bool b)
{
	posX = x;
	sprite = c;
	isWalkable = b;
}

int Case::GetPosX()
{
	return posX;
}

char Case::GetSprite()
{
	return sprite;
}

bool Case::GetIsWalkable()
{
	return isWalkable;
}

void Case::SetSprite(char c)
{
	sprite = c;
}