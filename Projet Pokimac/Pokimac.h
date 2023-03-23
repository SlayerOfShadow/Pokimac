#pragma once

#include <string>

using namespace std;

enum PokiType
{
	Fire,
	Water,
	Electric,
	Plant,
	Normal,
	Ground,
	Fighting
};

class Pokimac
{
private:
	string name;
	int level;
	int baseHealth;
	int baseAttack;
	int baseDefense;
	int baseSpeed;
	int currentHealth;
	int maxHealth;
	int attack;
	int defense;
	int speed;
	bool canBeCaptured;
	int currentExperience;
	int maxExperience;
	PokiType type;
public:
	Pokimac(string n, int lvl, int bh, int ba, int bd, int bs, bool capture, int currExp, PokiType type);
	string GetName();
	int GetLevel();
	int GetCurrentHealth();
	int GetMaxHealth();
	int GetAttack();
	int GetDefense();
	int GetSpeed();
	void SetCurrentHealth(int amount);
	void Attack(Pokimac* poki);
	bool GetCanBeCaptured();
	int GetCurrentExperience();
	int GetMaxExperience();
	void SetExperience(int amount);
	void LevelUp(int exp);
	PokiType GetPokiType();
	string EnumTypeToString();
};

