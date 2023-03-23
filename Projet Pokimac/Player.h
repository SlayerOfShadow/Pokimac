#pragma once

#include <string>

#include "Pokimac.h"

using namespace std;

class Player
{
private:
	string name;
	int posX;
	char sprite;
	bool inCombat;
	Pokimac* pokimacTeam[6];
	int nbPokimac;
public:
	Player(string s, int x, char c, bool b, int nPoki);
	string GetName();
	int GetPosX();
	void SetPosX(int x);
	char GetSprite();
	bool GetInCombat();
	void SetInCombat(bool b);
	int GetNbPokimac();
	void SetNbPokimac(int nb);
	Pokimac* GetPokimac(int index);
	void SetPokimac(Pokimac* poki, int index);
	void AddPokimac(Pokimac* pokimac);
	void SetPokimacTeam(Pokimac* team[6]);
};

