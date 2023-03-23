#pragma once

#include "Player.h"

class Case
{
private:
	int posX;
	char sprite;
	bool isWalkable;
public:
	Case(int x, char c, bool b);
	int GetPosX();
	char GetSprite();
	bool GetIsWalkable();
	void SetSprite(char c);
	virtual void StartCombat(Player* player) {};
};

