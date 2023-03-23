#pragma once

#include "Player.h"

void createMap();
void displayMapAndPlayer(Player* player);
void move(Player* player, char c);
void displayCombat(Player* player, Pokimac* pokimac);
void actionMenu(Player* player, Pokimac* pokimac);
void inventoryMenu(Player* player, Pokimac* pokimac);
void pokimacMenu(Player* player, Pokimac* pokimac);
void showConsoleCursor(bool showFlag);
void setCursorPosition(int x, int y);
void clearFromLine(int line);
void clearLine(int line);
void displayInfo(string info, int pos, int seconds);
void displayPokimacs(Player* player, Pokimac* pokimac);
void displayHPBar(Pokimac* poki, int x, int y);
void playerPokimacAttack(Player* player, Pokimac* pokimac);
void opponentPokimacAttack(Player* player, Pokimac* pokimac);
void displayEXPBar(Pokimac* poki, int x, int y);
void displayPlayerTeamInventory(Player* player);
void releaseMenu(Player* player, int c);