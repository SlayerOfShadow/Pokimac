#include <iostream>
#include <ctime>
#include <thread>         
#include <chrono>

#include "Grass.h"
#include "fonctions.h"


void Grass::StartCombat(Player* player)
{
	srand(time(NULL));

	int randomNumber = rand() % 4;

	if (randomNumber == 0)
	{
		player->SetInCombat(true);

		Pokimac* wildPoki;

		if (zone == 1)
		{
			int randomPoki = rand() % 3;

			switch (randomPoki)
			{
			case 0:
				wildPoki = new Pokimac("BULBASAUR", rand() % 3 + 2, 45, 57, 57, 45, true, 0, PokiType::Plant);
				displayCombat(player, wildPoki);
				break;
			case 1:
				wildPoki = new Pokimac("CHARMANDER", rand() % 3 + 2, 39, 56, 47, 65, true, 0, PokiType::Fire);
				displayCombat(player, wildPoki);
				break;
			case 2:
				wildPoki = new Pokimac("SQUIRTLE", rand() % 3 + 2, 44, 49, 65, 43, true, 0, PokiType::Water);
				displayCombat(player, wildPoki);
				break;
			default:
				break;
			}
		}
		else if (zone == 2)
		{
			int randomPoki = rand() % 2;

			switch (randomPoki)
			{
			case 0:
				wildPoki = new Pokimac("SANDSHREW", rand() % 3 + 5, 50, 48, 58, 40, true, 0, PokiType::Ground);
				displayCombat(player, wildPoki);
				break;
			case 1:
				wildPoki = new Pokimac("VULPIX", rand() % 3 + 5, 38, 46, 53, 65, true, 0, PokiType::Fire);
				displayCombat(player, wildPoki);
				break;
			case 2:
				wildPoki = new Pokimac("STARYU", rand() % 3 + 5, 30, 58, 55, 85, true, 0, PokiType::Water);
				displayCombat(player, wildPoki);
				break;
			default:
				break;
			}
		}
		else if (zone == 3)
		{
			int randomPoki = rand() % 2;

			switch (randomPoki)
			{
			case 0:
				wildPoki = new Pokimac("GROWLITHE", rand() % 3 + 8, 55, 70, 48, 60, true, 0, PokiType::Fire);
				displayCombat(player, wildPoki);
				break;
			case 1:
				wildPoki = new Pokimac("ODDISH", rand() % 3 + 8, 45, 63, 60, 30, true, 0, PokiType::Plant);
				displayCombat(player, wildPoki);
				break;
			case 2:
				wildPoki = new Pokimac("PSYDUCK", rand() % 3 + 8, 50, 59, 49, 55, true, 0, PokiType::Water);
				displayCombat(player, wildPoki);
				break;
			default:
				break;
			}
		}
	}
}

