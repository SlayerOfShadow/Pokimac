#include <iostream>
#include <Windows.h>
#include <conio.h> 
#include <thread>         
#include <chrono>

#include "fonctions.h"
#include "Inventory.h"
#include "Case.h"
#include "Grass.h"

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

int mapHorizontalSize = 80;
const int mapSize = 1600;
Case* map[mapSize];
int oldPosX;
char oldPosSprite;

int menuPosY = 23;
int opponentPosX = 24;
int playerPokiPosY = 9;
int vsPosX = 16;

int choice;
char entry;

Inventory inventory(10, 5, 10, 5);

void createMap()
{
	for (int i = 0; i < mapSize; i++)
	{
		//BORDERS
		if (i < mapHorizontalSize || i >= mapSize - mapHorizontalSize || (i - (mapHorizontalSize - 1)) % mapHorizontalSize == 0 || i % mapHorizontalSize == 0)
		{
			map[i] = new Case(i, '|', false);
		}
		
		//GRASS
		else if ((i > 1044 && i < 1049) || (i > 1125 && i < 1133) || (i > 1205 && i < 1213) || (i > 1286 && i < 1294))
		{
			map[i] = new Grass(i, 'x', true, 1);
		}
		else if ((i > 749 && i < 759) || (i > 830 && i < 840) || (i > 909 && i < 920) || (i > 987 && i < 998))
		{
			map[i] = new Grass(i, 'x', true, 2);
		}
		else if ((i > 298 && i < 304) || (i > 375 && i < 385) || (i > 455 && i < 465) || (i > 536 && i < 544))
		{
			map[i] = new Grass(i, 'x', true, 3);
		}

		//POKIMAC CENTER & ARENA
		else if((i >= 171 && i <= 177) || (i >= 330 && i <= 338) || (i >= 570 && i <= 572) || (i >= 576 && i <= 578) || i == 494
			|| i == 1263 || (i >= 1337 && i <= 1341) || (i >= 1345 && i <= 1349) || (i >= 1015 && i <= 1031) || (i >= 855 && i <= 871))
		{
			map[i] = new Case(i, '_', false);
		}
		else if (i == 573 || i == 575 || i == 569 || i == 489 || i == 409 || i == 579 || i == 499 || i == 419 
			|| i == 1344 || i == 1342 || i == 1257 || i == 1177 || i == 1269 || i == 1189)
		{
			map[i] = new Case(i, '|', false);
		}
		else if (i == 329 || i == 250 
			|| i == 1336 || i == 1110 || i == 934 || i == 1032)
		{
			map[i] = new Case(i, '/', false);
		}
		else if (i == 339 || i == 258 
			|| i == 1350 || i == 1096 || i == 1014 || i == 952)
		{
			map[i] = new Case(i, '\\', false);
		}
		else if (i == 574 || i == 1343)
		{
			map[i] = new Case(i, '.', true);
		}
		else if (i == 1183)
		{
			map[i] = new Case(i, 'A', false);
		}
		else if (i == 414)
		{
			map[i] = new Case(i, '+', false);
		}

		//ELSE
		else
		{
			map[i] = new Case(i, ' ', true);
		}
	}
}

void displayMapAndPlayer(Player* player)
{
	clearFromLine(0);

	for (int i = 0; i < mapSize; i++)
	{
		if (i > 0 && i % mapHorizontalSize == 0)
		{
			cout << '\n';
		}
		cout << map[i]->GetSprite();
	}

	setCursorPosition(player->GetPosX() % mapHorizontalSize, player->GetPosX() / mapHorizontalSize);
	cout << player->GetSprite();
}

void move(Player* player, char c)
{
	oldPosX = player->GetPosX();
	oldPosSprite = map[player->GetPosX()]->GetSprite();

	switch (c)
	{
	case KEY_UP:
		if (map[player->GetPosX() - mapHorizontalSize]->GetIsWalkable())
		{
			player->SetPosX(player->GetPosX() - mapHorizontalSize);
		}
		break;
	case KEY_LEFT:
		if (map[player->GetPosX() - 1]->GetIsWalkable())
		{
			player->SetPosX(player->GetPosX() - 1);
		}
		break;
	case KEY_DOWN:
		if (map[player->GetPosX() + mapHorizontalSize]->GetIsWalkable())
		{
			player->SetPosX(player->GetPosX() + mapHorizontalSize);
		}
		break;
	case KEY_RIGHT:
		if (map[player->GetPosX() + 1]->GetIsWalkable())
		{
			player->SetPosX(player->GetPosX() + 1);
		}
		break;
	default:
		break;
	}

	if (player->GetPosX() != oldPosX)
	{
		setCursorPosition(player->GetPosX() % mapHorizontalSize, player->GetPosX() / mapHorizontalSize);
		cout << player->GetSprite();
		setCursorPosition(oldPosX % mapHorizontalSize, oldPosX / mapHorizontalSize);
		cout << oldPosSprite;
		map[player->GetPosX()]->StartCombat(player);
		if (player->GetPosX() == 574)
		{
			for (int i = 0; i < player->GetNbPokimac(); i++)
			{
				player->GetPokimac(i)->SetCurrentHealth(player->GetPokimac(i)->GetMaxHealth());
			}
			displayInfo("All your PokImacs have been healed!", mapSize / mapHorizontalSize + 1, 2);
			clearLine(mapSize / mapHorizontalSize + 1);
		}
		if (player->GetPosX() == 1343)
		{
			Pokimac* bossPoki = new Pokimac("PERSIAN", 15, 65, 68, 63, 115, false, 0, PokiType::Normal);
			player->SetInCombat(true);
			displayCombat(player, bossPoki);
		}
	}
}

void displayCombat(Player* player, Pokimac* pokimac)
{
	displayInfo("You're getting attacked!", mapSize / mapHorizontalSize + 1, 2);

	displayPokimacs(player, pokimac);

	while (player->GetInCombat())
	{
		actionMenu(player, pokimac);
	}
}

void displayPokimacs(Player* player, Pokimac* pokimac)
{
	clearFromLine(0);

	setCursorPosition(opponentPosX, 0);
	cout << pokimac->GetName() << " Lv" << pokimac->GetLevel();
	setCursorPosition(opponentPosX, 1);
	cout << pokimac->EnumTypeToString();
	displayHPBar(pokimac, opponentPosX, 3);

	setCursorPosition(vsPosX, playerPokiPosY / 2 + 2);
	cout << "!VS!";

	setCursorPosition(0, playerPokiPosY);
	cout << player->GetPokimac(0)->GetName() << " Lv" << player->GetPokimac(0)->GetLevel() << "\n" << player->GetPokimac(0)->EnumTypeToString();
	displayHPBar(player->GetPokimac(0), 0, playerPokiPosY + 3);
	displayEXPBar(player->GetPokimac(0), 0, playerPokiPosY + 6);
	setCursorPosition(0, playerPokiPosY + 9);
	cout << "+ - - - - - - - - - - - - - - - - - +";
}

void displayHPBar(Pokimac* poki, int x, int y)
{
	int hp = ceil(poki->GetCurrentHealth() / (float)poki->GetMaxHealth() * 12);
	int i = 0;

	clearLine(y);
	setCursorPosition(x, y);

	cout << "HP" << "[";
	while (i < 12)
	{
		if (i < hp)
		{
			cout << "#";
		}
		else
		{
			cout << "-";
		}
		i += 1;
	}
	cout << "] " << poki->GetCurrentHealth() << "/" << poki->GetMaxHealth();
}

void displayEXPBar(Pokimac* poki, int x, int y)
{
	int exp = ceil(poki->GetCurrentExperience() / (float)poki->GetMaxExperience() * 25);
	int i = 0;

	clearLine(y);
	setCursorPosition(x, y);

	cout << "EXP" << "[";
	while (i < 25)
	{
		if (i < exp)
		{
			cout << "#";
		}
		else
		{
			cout << "-";
		}
		i += 1;
	}
	cout << "] " << poki->GetCurrentExperience() << "/" << poki->GetMaxExperience();
}

void actionMenu(Player* player, Pokimac* pokimac)
{
	choice = 0;
	clearFromLine(menuPosY - 2);

	cout << "What do you want to do?";

	while (true)
	{
		setCursorPosition(0, menuPosY);
		cout << "ATTACK  " << "\n" 
			<< "BAG  " << "\n" 
			<< "POKIMAC  " << "\n" 
			<< "RUN  ";

		switch (choice)
		{
			case 0:
				setCursorPosition(7, menuPosY);
				break;
			case 1:
				setCursorPosition(4, menuPosY + 1);
				break;
			case 2:
				setCursorPosition(8, menuPosY + 2);
				break;
			case 3:
				setCursorPosition(4, menuPosY + 3);
				break;
			default:
				break;
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
			case KEY_UP:
				choice -= 1;
				if (choice < 0) { choice = 3; }
				break;
			case KEY_DOWN:
				choice += 1;
				if (choice > 3) { choice = 0; }
				break;
			case 32:
				if (choice == 0)
				{
					clearFromLine(menuPosY);
					if (player->GetPokimac(0)->GetSpeed() >= pokimac->GetSpeed())
					{
						playerPokimacAttack(player, pokimac);
						if (pokimac->GetCurrentHealth() > 0)
						{
							opponentPokimacAttack(player, pokimac);
						}
					}
					else
					{
						Pokimac* tempPoki = player->GetPokimac(0);
						opponentPokimacAttack(player, pokimac);
						if (player->GetPokimac(0)->GetCurrentHealth() > 0 && player->GetPokimac(0) == tempPoki && player->GetInCombat())
						{
							playerPokimacAttack(player, pokimac);
						}
					}
					return;
				}
				if (choice == 1)
				{
					inventoryMenu(player, pokimac);
					return;
				}
				if (choice == 2)
				{
					pokimacMenu(player, pokimac);
					return;
				}
				if (choice == 3) 
				{ 
					if (player->GetPosX() != 1343)
					{
						displayInfo("You decided to run away!", menuPosY - 2, 1);
						player->SetInCombat(false);
						delete pokimac;
						displayMapAndPlayer(player);
						return;
					}
					else
					{
						displayInfo("You can't run away against the arena boss!", menuPosY - 2, 1);
						clearLine(menuPosY - 2);
						cout << "What do you want to do?";
					}
				}
				break;
			default:
				break;
		}
	}
}

void playerPokimacAttack(Player* player, Pokimac* pokimac)
{
	displayInfo(player->GetPokimac(0)->GetName() + " attack!", menuPosY - 2, 1);
	player->GetPokimac(0)->Attack(pokimac);
	displayHPBar(pokimac, opponentPosX, 3);
	if (pokimac->GetCurrentHealth() == 0)
	{
		int oldLevel = player->GetPokimac(0)->GetLevel();
		displayInfo(pokimac->GetName() + " is K.O!", menuPosY - 2, 2);
		displayInfo(player->GetPokimac(0)->GetName() + " gained " + to_string(80 * pokimac->GetLevel() / 7) + " experience!", menuPosY - 2, 2);
		player->GetPokimac(0)->SetExperience(player->GetPokimac(0)->GetCurrentExperience() + (80 * pokimac->GetLevel() / 7));
		if (player->GetPokimac(0)->GetLevel() != oldLevel)
		{
			displayPokimacs(player, pokimac);
			displayInfo(player->GetPokimac(0)->GetName() + " leveled up!", menuPosY - 2, 2);
		}
		else
		{
			displayEXPBar(player->GetPokimac(0), 0, playerPokiPosY + 6);
		}

		if (player->GetPosX() == 1343)
		{
			clearFromLine(0);
			cout << "##############################################################################################\n"
				<< "##                                                                                          ##\n"
				<< "##                     ______      ______      ____      ____  _______                      ##\n"
				<< "##                   .' ___  |   .' ___  |    |_  _|    |_  _||_   __ \\                     ##\n"
				<< "##                  / .'   \\_|  / .'   \\_|      \\ \\  /\\  / /    | |__) |                    ##\n"
				<< "##                  | |   ____  | |   ____       \\ \\/  \\/ /     |  ___/                     ##\n"
				<< "##                  \\ `.___]  | \\ `.___]  |       \\  /\\  /     _| |_                        ##\n"
				<< "##                   `._____.'   `._____.'         \\/  \\/     |_____|                       ##\n"
				<< "##                                                                                          ##\n"
				<< "##                                                                                          ##\n"
				<< "##                  You have defeated the arena champion, CONGRATULATIONS!                  ##\n"
				<< "##                                   Thanks for playing!                                    ##\n"
				<< "##                                                                                          ##\n"
				<< "##                               __ __ __ __ __ __ __ __ __                                 ##\n"
				<< "##           ______  ______  ___   ___  ________ ___ __ __  ________  ______                ##\n"
				<< "##          /_____/\\/_____/\\/___/\\/__/\\/_______//__//_//_/\\/_______/\\/_____/\\               ##\n"
				<< "##          \\:::_ \\ \\:::_ \\ \\::.\\ \\\\ \\ \\__.::._\\\\::\\| \\| \\ \\::: _  \\ \\:::__\\/               ##\n"
				<< "##           \\:(_) \\ \\:\\ \\ \\ \\:: \\/_) \\ \\ \\::\\ \\ \\:.      \\ \\::(_)  \\ \\:\\ \\  __             ##\n"
				<< "##            \\: ___\\/\\:\\ \\ \\ \\:. __  ( ( _\\::\\ \\_\\:.\\-/\\  \\ \\:: __  \\ \\:\\ \\/_/\\            ##\n"
				<< "##             \\ \\ \\   \\:\\_\\ \\ \\: \\ )  \\ /__\\::\\__/\\. \\  \\  \\ \\:.\\ \\  \\ \\:\\_\\ \\ \\           ##\n"
				<< "##              \\_\\/    \\_____\\/\\__\\/\\__\\\\________\\/\\__\\/ \\__\\/\\__\\/\\__\\/\\_____\\/           ##\n"
				<< "##                               __ __ __ __ __ __ __ __ __                                 ##\n"
				<< "##                                                                                          ##\n"
				<< "##                                         by Antoine Leblond and Benjamin Razafimanantsoa  ##\n"
				<< "##############################################################################################\n";
			exit(0);
		}
		else
		{
			displayInfo("The fight is over!", menuPosY - 2, 1);
			player->SetInCombat(false);
			delete pokimac;
			displayMapAndPlayer(player);
		}
	}
}

void opponentPokimacAttack(Player* player, Pokimac* pokimac)
{
	displayInfo(pokimac->GetName() + " attack!", menuPosY - 2, 1);
	pokimac->Attack(player->GetPokimac(0));
	displayHPBar(player->GetPokimac(0), 0, playerPokiPosY + 3);
	if (player->GetPokimac(0)->GetCurrentHealth() == 0)
	{
		displayInfo(player->GetPokimac(0)->GetName() + " is K.O!", menuPosY - 2, 2);
		for (int i = 0; i < player->GetNbPokimac(); i++)
		{
			if (player->GetPokimac(i)->GetCurrentHealth() > 0)
			{
				displayInfo(player->GetPokimac(0)->GetName() + " was changed with " + player->GetPokimac(i)->GetName() + "!", menuPosY - 2, 1);
				Pokimac* tempPoki = player->GetPokimac(0);
				player->SetPokimac(player->GetPokimac(i), 0);
				player->SetPokimac(tempPoki, i);
				displayPokimacs(player, pokimac);
				return;
			}
		}
		displayInfo("All your PokImacs are K.O., back to the PokImac center!", menuPosY - 2, 2);
		player->SetInCombat(false);
		player->SetPosX(574);
		for (int i = 0; i < player->GetNbPokimac(); i++)
		{
			player->GetPokimac(i)->SetCurrentHealth(player->GetPokimac(i)->GetMaxHealth());
		}
		displayMapAndPlayer(player);
		return;
	}
}

void inventoryMenu(Player* player, Pokimac* pokimac)
{
	choice = 0;
	clearFromLine(menuPosY - 2);

	cout << "Which item do you want to use?";

	while (true)
	{
		setCursorPosition(0, menuPosY);
		cout << "Potion x" << inventory.GetNbPotion() << "   " << "\n"
			<< "SuperPotion x" << inventory.GetNbSuperPotion() << "   " << "\n"
			<< "PokiBall x" << inventory.GetNbPokiBall() << "   " << "\n"
			<< "SuperPokiBall x" << inventory.GetNbSuperPokiBall() << "   " << "\n"
			<< "BACK  ";

		switch (choice)
		{
			case 0:
				setCursorPosition(inventory.GetNbPotion() < 10 ? 10 : 11, menuPosY);
				break;
			case 1:
				setCursorPosition(inventory.GetNbSuperPotion() < 10 ? 15 : 16, menuPosY + 1);
				break;
			case 2:
				setCursorPosition(inventory.GetNbPokiBall() < 10 ? 12 : 13, menuPosY + 2);
				break;
			case 3:
				setCursorPosition(inventory.GetNbSuperPokiBall() < 10 ? 17 : 18, menuPosY + 3);
				break;
			case 4:
				setCursorPosition(5, menuPosY + 4);
			default:
				break;
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
			case KEY_UP:
				choice -= 1;
				if (choice < 0) { choice = 4; }
				break;
			case KEY_DOWN:
				choice += 1;
				if (choice > 4) { choice = 0; }
				break;
			case 32:
				if (choice == 0)
				{
					if (inventory.GetNbPotion() > 0)
					{
						if (player->GetPokimac(0)->GetCurrentHealth() < player->GetPokimac(0)->GetMaxHealth())
						{
							clearFromLine(menuPosY);
							if (player->GetPokimac(0)->GetMaxHealth() - player->GetPokimac(0)->GetCurrentHealth() > 20)
							{
								displayInfo(player->GetPokimac(0)->GetName() + " was healed for 20HP!", menuPosY - 2, 1);
							}
							else
							{
								displayInfo(player->GetPokimac(0)->GetName() + " was healed for " + to_string(player->GetPokimac(0)->GetMaxHealth() - player->GetPokimac(0)->GetCurrentHealth()) + "HP!", menuPosY - 2, 1);
							}
							player->GetPokimac(0)->SetCurrentHealth(player->GetPokimac(0)->GetCurrentHealth() + 20);
							inventory.SetNbPotion(inventory.GetNbPotion() - 1);
							displayHPBar(player->GetPokimac(0), 0, playerPokiPosY + 3);
							opponentPokimacAttack(player, pokimac);
							return;
						}
						else
						{
							displayInfo(player->GetPokimac(0)->GetName() + "'s HP are already at their maximum!", menuPosY - 2, 1);
							clearLine(menuPosY - 2);
							cout << "Which item do you want to use?";
						}
					}
					else
					{
						displayInfo("You don't have any Potion left!", menuPosY - 2, 1);
						clearLine(menuPosY - 2);
						cout << "Which item do you want to use?";
					}
				}
				if (choice == 1)
				{
					if (inventory.GetNbSuperPotion() > 0)
					{
						if (player->GetPokimac(0)->GetCurrentHealth() < player->GetPokimac(0)->GetMaxHealth())
						{
							clearFromLine(menuPosY);
							if (player->GetPokimac(0)->GetMaxHealth() - player->GetPokimac(0)->GetCurrentHealth() > 50)
							{
								displayInfo(player->GetPokimac(0)->GetName() + " was healed for 50HP!", menuPosY - 2, 1);
							}
							else
							{
								displayInfo(player->GetPokimac(0)->GetName() + " was healed for " + to_string(player->GetPokimac(0)->GetMaxHealth() - player->GetPokimac(0)->GetCurrentHealth()) + "HP!", menuPosY - 2, 1);
							}
							player->GetPokimac(0)->SetCurrentHealth(player->GetPokimac(0)->GetCurrentHealth() + 50);
							inventory.SetNbSuperPotion(inventory.GetNbSuperPotion() - 1);
							displayHPBar(player->GetPokimac(0), 0, playerPokiPosY + 3);
							opponentPokimacAttack(player, pokimac);
							return;
						}
						else
						{
							displayInfo(player->GetPokimac(0)->GetName() + "'s HP are already at their maximum!", menuPosY - 2, 1);
							clearLine(menuPosY - 2);
							cout << "Which item do you want to use?";
						}
					}
					else
					{
						displayInfo("You don't have any SuperPotion left!", menuPosY - 2, 1);
						clearLine(menuPosY - 2);
						cout << "Which item do you want to use?";
					}
				}
				if (choice == 2)
				{
					if (inventory.GetNbPokiBall() > 0)
					{
						if (pokimac->GetCanBeCaptured())
						{
							if (player->GetNbPokimac() < 6)
							{
								srand(time(NULL));
								int captureRate = round((2 - pokimac->GetCurrentHealth() / (float)pokimac->GetMaxHealth()) * 25);
								int randomNumber = rand() % 100;

								if (randomNumber > 0 && randomNumber <= captureRate)
								{
									clearFromLine(menuPosY);
									displayInfo("You successfully captured " + pokimac->GetName() + "!", menuPosY - 2, 2);
									player->AddPokimac(pokimac);
									inventory.SetNbPokiBall(inventory.GetNbPokiBall() - 1);
									player->SetInCombat(false);
									clearFromLine(0);
									displayMapAndPlayer(player);
									return;
								}
								else
								{
									clearFromLine(menuPosY);
									displayInfo("You missed the PokiBall!", menuPosY - 2, 1);
									inventory.SetNbPokiBall(inventory.GetNbPokiBall() - 1);
									opponentPokimacAttack(player, pokimac);
									return;
								}
							}
							else
							{
								displayInfo("Your team is full!", menuPosY - 2, 1);
								clearLine(menuPosY - 2);
								cout << "Which item do you want to use?";
							}
						}
						else
						{
							displayInfo("You can't capture this PokImac!", menuPosY - 2, 1);
							clearLine(menuPosY - 2);
							cout << "Which item do you want to use?";
						}
					}
					else
					{
						displayInfo("You don't have any PokiBall left!", menuPosY - 2, 1);
						clearLine(menuPosY - 2);
						cout << "Which item do you want to use?";
					}
				}
				if (choice == 3)
				{
					if (inventory.GetNbSuperPokiBall() > 0)
					{
						if (pokimac->GetCanBeCaptured())
						{
							if (player->GetNbPokimac() < 6)
							{
								srand(time(NULL));
								int captureRate = round((2 - pokimac->GetCurrentHealth() / (float)pokimac->GetMaxHealth()) * 50);
								int randomNumber = rand() % 100;

								if (randomNumber > 0 && randomNumber <= captureRate)
								{
									clearFromLine(menuPosY);
									displayInfo("You successfully captured " + pokimac->GetName() + "!", menuPosY - 2, 2);
									player->AddPokimac(pokimac);
									inventory.SetNbSuperPokiBall(inventory.GetNbSuperPokiBall() - 1);
									player->SetInCombat(false);
									displayMapAndPlayer(player);
									return;
								}
								else
								{
									clearFromLine(menuPosY);
									displayInfo("You missed the SuperPokiBall!", menuPosY - 2, 1);
									inventory.SetNbSuperPokiBall(inventory.GetNbSuperPokiBall() - 1);
									opponentPokimacAttack(player, pokimac);
									return;
								}
							}
							else
							{
								displayInfo("Your team is full!", menuPosY - 2, 1);
								clearLine(menuPosY - 2);
								cout << "Which item do you want to use?";
							}
						}
						else
						{
							displayInfo("You can't capture this PokImac!", menuPosY - 2, 1);
							clearLine(menuPosY - 2);
							cout << "Which item do you want to use?";
						}
					}
					else
					{
						displayInfo("You don't have any SuperPokiBall left!", menuPosY - 2, 1);
						clearLine(menuPosY - 2);
						cout << "Which item do you want to use?";
					}
				}
				if (choice == 4)
				{
					actionMenu(player, pokimac);
					return;
				}
				break;
			default:
				break;
		}
	}
}

void pokimacMenu(Player* player, Pokimac* pokimac)
{
	choice = 0;
	clearFromLine(menuPosY - 2);

	cout << "Swap with which PokImac?";

	while (true)
	{
		for (int i = 0; i < player->GetNbPokimac(); i++)
		{
			setCursorPosition(0, i + menuPosY);
			cout << player->GetPokimac(i)->GetName() << " Lv" << player->GetPokimac(i)->GetLevel() << "  ";
		}
		cout << "\nBACK  ";

		if (choice == player->GetNbPokimac())
		{
			setCursorPosition(5, player->GetNbPokimac() + menuPosY);
		}
		else
		{
			if (player->GetPokimac(choice)->GetLevel() < 10)
			{
				setCursorPosition(player->GetPokimac(choice)->GetName().length() + 5, choice + menuPosY);
			}
			else
			{
				setCursorPosition(player->GetPokimac(choice)->GetName().length() + 6, choice + menuPosY);
			}
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
		case KEY_UP:
			choice -= 1;
			if (choice < 0) { choice = player->GetNbPokimac(); }
			break;
		case KEY_DOWN:
			choice += 1;
			if (choice > player->GetNbPokimac()) { choice = 0; }
			break;
		case 32:
			if (choice == player->GetNbPokimac())
			{
				actionMenu(player, pokimac);
				return;
			}
			else if (choice == 0)
			{
				displayInfo(player->GetPokimac(0)->GetName() + " is already on the field!", menuPosY - 2, 1);
				clearLine(menuPosY - 2);
				cout << "Swap with which PokImac?";
			}
			else if (player->GetPokimac(choice)->GetCurrentHealth() == 0)
			{
				displayInfo(player->GetPokimac(choice)->GetName() + " is K.O, you can't swap with him!", menuPosY - 2, 1);
				clearLine(menuPosY - 2);
				cout << "Swap with which PokImac?";
			}
			else
			{
				clearFromLine(menuPosY);
				displayInfo("You swaped " + player->GetPokimac(0)->GetName() + " for " + player->GetPokimac(choice)->GetName() + "!", menuPosY - 2, 1);
				Pokimac* tempPoki = player->GetPokimac(0);
				player->SetPokimac(player->GetPokimac(choice), 0);
				player->SetPokimac(tempPoki, choice);
				displayPokimacs(player, pokimac);
				opponentPokimacAttack(player, pokimac);
				return;
			}
			break;
		default:
			break;
		}
	}
}

void displayPlayerTeamInventory(Player* player)
{
	choice = 0;
	clearFromLine(0);

	while (true)
	{
		setCursorPosition(0, 0);
		cout << player->GetName() << "'s team :";
		setCursorPosition(30, 0);
		cout << "Your inventory :";
		setCursorPosition(30, 2);
		cout << "Potion x" << inventory.GetNbPotion();
		setCursorPosition(30, 3);
		cout << "SuperPotion x" << inventory.GetNbSuperPotion();
		setCursorPosition(30, 4);
		cout << "PokiBall x" << inventory.GetNbPokiBall();
		setCursorPosition(30, 5);
		cout << "SuperPokiBall x" << inventory.GetNbSuperPokiBall();

		for (int i = 0; i < player->GetNbPokimac(); i++)
		{
			setCursorPosition(0, i + 2);
			cout << player->GetPokimac(i)->GetName() << " Lv" << player->GetPokimac(i)->GetLevel() << "  ";
		}
		cout << "\nBACK  ";

		clearFromLine(10);

		if (choice == player->GetNbPokimac())
		{
			setCursorPosition(5, player->GetNbPokimac() + 2);
		}
		else
		{
			cout << "Stats :" << "\n\n"
			 << "HP " << player->GetPokimac(choice)->GetCurrentHealth() << "/" << player->GetPokimac(choice)->GetMaxHealth() << "\n"
			 << "EXP " << player->GetPokimac(choice)->GetCurrentExperience() << "/" << player->GetPokimac(choice)->GetMaxExperience() << "\n\n"
			 << "ATK " << player->GetPokimac(choice)->GetAttack() << "\n"
			 << "DEF " << player->GetPokimac(choice)->GetDefense() << "\n"
			 << "SPD " << player->GetPokimac(choice)->GetSpeed() << "\n";
			
			if (player->GetPokimac(choice)->GetLevel() < 10)
			{
				setCursorPosition(player->GetPokimac(choice)->GetName().length() + 5, choice + 2);
			}
			else
			{
				setCursorPosition(player->GetPokimac(choice)->GetName().length() + 6, choice + 2);
			}
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
		case KEY_UP:
			choice -= 1;
			if (choice < 0) { choice = player->GetNbPokimac(); }
			break;
		case KEY_DOWN:
			choice += 1;
			if (choice > player->GetNbPokimac()) { choice = 0; }
			break;
		case 32:
			if (choice == player->GetNbPokimac())
			{
				displayMapAndPlayer(player);
				return;
			}
			else
			{
				if (player->GetNbPokimac() > 1)
				{
					releaseMenu(player, choice);
					break;
				}
			}
		default:
			break;
		}
	}
}

void releaseMenu(Player* player, int c)
{
	int releaseChoice = 0;
	setCursorPosition(0, 19);
	cout << "Do you want to release " << player->GetPokimac(c)->GetName() << "?";

	while (true)
	{
		setCursorPosition(0, 21);
		cout << "No  " << "\n"
			<< "Yes  ";

		switch (releaseChoice)
		{
		case 0:
			setCursorPosition(3, 21);
			break;
		case 1:
			setCursorPosition(4, 22);
			break;
		default:
			break;
		}
		cout << "<";

		entry = _getch();

		switch (entry)
		{
		case KEY_UP:
			releaseChoice -= 1;
			if (releaseChoice < 0) { releaseChoice = 1; }
			break;
		case KEY_DOWN:
			releaseChoice += 1;
			if (releaseChoice > 1) { releaseChoice = 0; }
			break;
		case 32:
			if (releaseChoice == 0)
			{
				clearFromLine(19);
				return;
			}
			else if (releaseChoice == 1)
			{
				clearFromLine(19);
				displayInfo(player->GetPokimac(c)->GetName() + " was succesfully released!", 19, 2);
				player->SetNbPokimac(player->GetNbPokimac() - 1);
				int y = 0;
				for (int i = 0; i < player->GetNbPokimac(); i++)
				{
					if (i == c)
					{
						y++;
					}
					player->SetPokimac(player->GetPokimac(y), i);
					y++;
				}
				clearFromLine(0);
				return;
			}
		}
	}
}

void displayInfo(string info, int pos, int seconds)
{
	clearLine(pos);
	cout << info;
	this_thread::sleep_for(chrono::seconds(seconds));
	while (_kbhit())
	{
		_getch();
	}
}

void clearFromLine(int line)
{
	setCursorPosition(0, line);
	cout << "\x1B[0J";
}

void clearLine(int line)
{
	setCursorPosition(0, line);
	cout << "\x1B[2K";
}

void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setCursorPosition(int x, int y)
{
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
