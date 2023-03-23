#include "Player.h"

Player::Player(string s, int x, char c, bool b, int nPoki)
{
	name = s;
	posX = x;
	sprite = c;
	inCombat = b;
	nbPokimac = nPoki;
}

string Player::GetName()
{
	return name;
}

int Player::GetPosX()
{
	return posX;
}

void Player::SetPosX(int x)
{
	posX = x;
}

char Player::GetSprite()
{
	return sprite;
}

bool Player::GetInCombat()
{
	return inCombat;
}

void Player::SetInCombat(bool b)
{
	inCombat = b;
}

int Player::GetNbPokimac()
{
	return nbPokimac;
}

void Player::SetNbPokimac(int nb)
{
	nbPokimac = nb;
}

Pokimac* Player::GetPokimac(int index)
{
	return pokimacTeam[index];
}

void Player::SetPokimac(Pokimac* poki, int index)
{
	pokimacTeam[index] = poki;
}

void Player::AddPokimac(Pokimac* pokimac)
{
	if (nbPokimac < 6)
	{
		pokimacTeam[nbPokimac] = pokimac;
		nbPokimac += 1;
	}
}

void Player::SetPokimacTeam(Pokimac* team[6])
{
	*pokimacTeam = *team;
}
