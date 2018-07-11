//
// Created by xinbochao on 18-1-13.
//

#ifndef HOARDING_GAME_H
#define HOARDING_GAME_H
#include "Property.h"

namespace Monopoly {
bool isGameEnd(vector<Player> &playerGroup, Gamestate &gamestate);
bool playerTurn(vector<Player> &playerGroup, Board &map, unsigned int &playerIndex, bool someoneLeave);
void printWinner(vector<Player> &playerGroup);
void displayMap(const vector<Player> &playerGroup, const Board &map);
}
#endif
