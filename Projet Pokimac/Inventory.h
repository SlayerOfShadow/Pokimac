#pragma once

class Inventory
{
private:
	int nbPotion;
	int nbSuperPotion;
	int nbPokiBall;
	int nbSuperPokiBall;
public:
	Inventory(int potion, int superPotion, int pokiBall, int superPokiBall);
	int GetNbPotion();
	int GetNbSuperPotion();
	int GetNbPokiBall();
	int GetNbSuperPokiBall();
	void SetNbPotion(int amount);
	void SetNbSuperPotion(int amount);
	void SetNbPokiBall(int amount);
	void SetNbSuperPokiBall(int amount);
};

