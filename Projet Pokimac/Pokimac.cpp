#include <cmath>
#include <ctime>

#include "Pokimac.h"
#include "fonctions.h"

Pokimac::Pokimac(string n, int lvl, int bh, int ba, int bd, int bs, bool capture, int currExp, PokiType t)
{
	name = n;
	level = lvl;
	baseHealth = bh;
	baseAttack = ba;
	baseDefense = bd;
	baseSpeed = bs;
	maxHealth = round(2 * baseHealth * level / (float)100) + level + 10;
	currentHealth = maxHealth;
	attack = round(2 * baseAttack * level / (float)100) + 5;
	defense = round(2 * baseDefense * level / (float)100) + 5;
	speed = round(2 * baseSpeed * level / (float)100) + 5;
	canBeCaptured = capture;
	currentExperience = currExp;
	maxExperience = pow(level, 3) - pow(level - 1, 3);
	type = t;
}

string Pokimac::GetName()
{
	return name;
}

int Pokimac::GetLevel()
{
	return level;
}

int Pokimac::GetCurrentHealth()
{
	return currentHealth;
}

int Pokimac::GetMaxHealth()
{
	return maxHealth;
}

int Pokimac::GetAttack()
{
	return attack;
}

int Pokimac::GetDefense()
{
	return defense;
}

int Pokimac::GetSpeed()
{
	return speed;
}

void Pokimac::SetCurrentHealth(int amount)
{
	currentHealth = amount;

	if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}
	if (currentHealth < 0)
	{
		currentHealth = 0;
	}
}

bool Pokimac::GetCanBeCaptured()
{
	return canBeCaptured;
}

int Pokimac::GetMaxExperience()
{
	return maxExperience;
}

void Pokimac::SetExperience(int amount)
{
	currentExperience = amount;
	if (currentExperience >= maxExperience)
	{
		int exp = currentExperience - maxExperience;
		LevelUp(exp);
	}
}

int Pokimac::GetCurrentExperience()
{
	return currentExperience;
}

void Pokimac::Attack(Pokimac* poki)
{
	srand(time(NULL));

	int randomNumber = rand() % 10;

	int damage = round(((level * 0.4 + 2) * attack * 50) / (poki->GetDefense() * 50));

	if (randomNumber == 0)
	{
		damage = damage * 2;
		displayInfo("Critical hit!", 21, 1);
		clearLine(21);
	}

	switch (type)
	{
		case Fire:
			if (poki->GetPokiType() == Plant)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Water || poki->GetPokiType() == Fire)
			{
				damage = damage / 2;
				displayInfo("It's not very effective...", 21, 1);
				clearLine(21);
			}
			break;
		case Water:
			if (poki->GetPokiType() == Fire || poki->GetPokiType() == Ground)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Plant || poki->GetPokiType() == Water)
			{
				damage = damage / 2;
				displayInfo("It's not very effective...", 21, 1);
				clearLine(21);
			}
			break;
		case Electric:
			if (poki->GetPokiType() == Water)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Plant || poki->GetPokiType() == Electric)
			{
				damage = damage / 2;
				displayInfo("It's not very effective...", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Ground)
			{
				damage = 0;
				displayInfo("It doesn't affect " + poki->GetName() + "...", 21, 1);
				clearLine(21);
			}
			break;
		case Plant:
			if (poki->GetPokiType() == Water || poki->GetPokiType() == Ground)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Plant || poki->GetPokiType() == Fire)
			{
				damage = damage / 2;
				displayInfo("It's not very effective...", 21, 1);
				clearLine(21);
			}
			break;
		case Ground:
			if (poki->GetPokiType() == Fire || poki->GetPokiType() == Electric)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			if (poki->GetPokiType() == Plant)
			{
				damage = damage / 2;
				displayInfo("It's not very effective...", 21, 1);
				clearLine(21);
			}
			break;
		case Fighting:
			if (poki->GetPokiType() == Normal)
			{
				damage = damage * 2;
				displayInfo("It's very effective!", 21, 1);
				clearLine(21);
			}
			break;
		default:
			break;
	}

	poki->SetCurrentHealth(poki->GetCurrentHealth() - damage);
}

void Pokimac::LevelUp(int exp)
{
	int oldMaxHealth = maxHealth;
	level += 1;
	if (level > 99)
	{
		level = 99;
	}
	maxHealth = round(2 * baseHealth * level / (float)100) + level + 10;
	attack = round(2 * baseAttack * level / (float)100) + 5;
	defense = round(2 * baseDefense * level / (float)100) + 5;
	speed = round(2 * baseSpeed * level / (float)100) + 5;
	SetCurrentHealth(currentHealth + maxHealth - oldMaxHealth);
	currentExperience = exp;
	maxExperience = pow(level, 3) - pow(level-1, 3);
	if (currentExperience >= maxExperience)
	{
		int exp = currentExperience - maxExperience;
		LevelUp(exp);
	}
}

PokiType Pokimac::GetPokiType()
{
	return type;
}

string Pokimac::EnumTypeToString()
{
	switch (type)
	{
	case Fire:
		return "Fire";
		break;
	case Water:
		return "Water";
		break;
	case Electric:
		return "Electric";
		break;
	case Plant:
		return "Grass";
		break;
	case Normal:
		return "Normal";
		break;
	case Ground:
		return "Ground";
		break;
	case Fighting:
		return "Fighting";
		break;
	default:
		break;
	}
}

/* FONCTION QUI PERMET DE RECUPERER UN SPRITE DANS UN FICHIER .txt
   INCLURE <fstream> ET <sstream>
   OBSOLETE
void Pokimac::SetSprite(string fileName)
{
	ifstream spriteFile;
	ostringstream oss;
	spriteFile.open(fileName);
	oss << spriteFile.rdbuf();
	sprite = oss.str();
}
*/