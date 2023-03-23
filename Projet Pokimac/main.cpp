#include <iostream>
#include <conio.h>

#include "fonctions.h"

using namespace std;

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

int main()
{
	string playerName;
	cout << "##############################################################################################\n"
		<< "##                                                                                          ##\n"
		<< "##                                                                                          ##\n"
		<< "##           ______  ______  ___   ___  ________ ___ __ __  ________  ______                ##\n"
		<< "##          /_____/\\/_____/\\/___/\\/__/\\/_______//__//_//_/\\/_______/\\/_____/\\               ##\n"
		<< "##          \\:::_ \\ \\:::_ \\ \\::.\\ \\\\ \\ \\__.::._\\\\::\\| \\| \\ \\::: _  \\ \\:::__\\/               ##\n"
		<< "##           \\:(_) \\ \\:\\ \\ \\ \\:: \\/_) \\ \\ \\::\\ \\ \\:.      \\ \\::(_)  \\ \\:\\ \\  __             ##\n"
		<< "##            \\: ___\\/\\:\\ \\ \\ \\:. __  ( ( _\\::\\ \\_\\:.\\-/\\  \\ \\:: __  \\ \\:\\ \\/_/\\            ##\n"
		<< "##             \\ \\ \\   \\:\\_\\ \\ \\: \\ )  \\ /__\\::\\__/\\. \\  \\  \\ \\:.\\ \\  \\ \\:\\_\\ \\ \\           ##\n"
		<< "##              \\_\\/    \\_____\\/\\__\\/\\__\\\\________\\/\\__\\/ \\__\\/\\__\\/\\__\\/\\_____\\/           ##\n"
		<< "##                                                                                          ##\n"
		<< "##                                                                                          ##\n"
		<< "##                                                                                          ##\n"
		<< "##  As in Pokemon your goal is to capture PokImacs, gain experience and defeat the arena!   ##\n"
		<< "##                             			                                            ##\n"
		<< "##      You'll start with different items in your inventory and chose your starter!         ##\n"
		<< "##                            		                                                    ##\n"
		<< "##   You are represented with a 'P' and the grass is represented with a 'x' on the map.     ##\n"
		<< "##                           			                                            ##\n"
		<< "##  You can't have more than 6 PokImacs in your team, so think before capturing a PokImac!  ##\n"
		<< "##                           			                                            ##\n"
		<< "## CONTROLS : - Move with ARROWKEY                        			            ##\n"
		<< "##            - Interact with SPACEBAR                                                      ##\n"
		<< "##            - Open your inventory with A                                                  ##\n"
		<< "##                               	                                                    ##\n"
		<< "##             You can heal your PokImacs by going to the PokImac center.                   ##\n"
		<< "##    If all your PokImacs are K.O. you go back to the PokImac center, so be careful!       ##\n"
		<< "##                                                                                          ##\n"
		<< "##############################################################################################\n\n"

		<< "Are you ready? If so, please enter your trainer name: ";


	getline(cin, playerName);

	Player* player = new Player(playerName, 564, 'P', false, 0);

	showConsoleCursor(false);

	char entry;
	int starterChoice = 0;
	bool starter = false;
	Pokimac* starterPoki;
	cout << "\nNice to see you " << playerName << "! Now choose your starter:\n\n";

	while (!starter)
	{
		setCursorPosition(0, 34);
		cout << "PIKACHU  " << "\n"
			<< "MACHOP  " << "\n"
			<< "JIGGLYPUFF  ";

		switch (starterChoice)
		{
		case 0:
			setCursorPosition(8, 34);
			break;
		case 1:
			setCursorPosition(7, 35);
			break;
		case 2:
			setCursorPosition(11, 36);
			break;
		default:
			break;
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
		case KEY_UP:
			starterChoice -= 1;
			if (starterChoice < 0) { starterChoice = 2; }
			break;
		case KEY_DOWN:
			starterChoice += 1;
			if (starterChoice > 2) { starterChoice = 0; }
			break;
		case 32:
			if (starterChoice == 0)
			{
				starterPoki = new Pokimac("PIKACHU", 5, 35, 53, 45, 90, true, 0, PokiType::Electric);
				player->AddPokimac(starterPoki);
				clearFromLine(32);
				displayInfo(starterPoki->GetName() + " is a great choice! Now it's time to begin your adventure, good luck!", 32, 3);
			}
			else if (starterChoice == 1)
			{
				starterPoki = new Pokimac("MACHOP", 5, 70, 58, 43, 35, true, 0, PokiType::Fighting);
				player->AddPokimac(starterPoki);
				clearFromLine(32);
				displayInfo(starterPoki->GetName() + " is a great choice! Now it's time to begin your adventure, good luck!", 32, 3);
			}
			else if (starterChoice == 2)
			{
				starterPoki = new Pokimac("JIGGLYPUFF", 5, 115, 45, 23, 20, true, 0, PokiType::Normal);
				player->AddPokimac(starterPoki);
				clearFromLine(32);
				displayInfo(starterPoki->GetName() + " is a great choice! Now it's time to begin your adventure, good luck!", 32, 3);
			}
			starter = true;
			break;
		default:
			break;
		}
	}

	createMap();
	displayMapAndPlayer(player);

	while (!player->GetInCombat())
	{
		entry = _getch();
		if (entry == 'i')
		{
			displayPlayerTeamInventory(player);
		}
		else
		{
			move(player, entry);
		}
	}

	return 0;
}