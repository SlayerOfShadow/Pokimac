#include "Inventory.h"

Inventory::Inventory(int potion, int superPotion, int pokiBall, int superPokiBall)
{
	nbPotion = potion;
	nbSuperPotion = superPotion;
	nbPokiBall = pokiBall;
	nbSuperPokiBall = superPokiBall;
}

int Inventory::GetNbPotion()
{
	return nbPotion;
}

int Inventory::GetNbSuperPotion()
{
	return nbSuperPotion;
}

int Inventory::GetNbPokiBall()
{
	return nbPokiBall;
}

int Inventory::GetNbSuperPokiBall()
{
	return nbSuperPokiBall;
}

void Inventory::SetNbPotion(int amount)
{
	nbPotion = amount;
	if (nbPotion > 99)
	{
		nbPotion = 99;
	}
}

void Inventory::SetNbSuperPotion(int amount)
{
	nbSuperPotion = amount;
	if (nbSuperPotion > 99)
	{
		nbSuperPotion = 99;
	}
}

void Inventory::SetNbPokiBall(int amount)
{
	nbPokiBall = amount;
	if (nbPokiBall > 99)
	{
		nbPokiBall = 99;
	}
}

void Inventory::SetNbSuperPokiBall(int amount)
{
	nbSuperPokiBall = amount;
	if (nbSuperPokiBall > 99)
	{
		nbSuperPokiBall = 99;
	}
}
