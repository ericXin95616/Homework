//
// Created by xinbochao on 18-1-13.
//

#ifndef HOARDING_SETGAME_H
#define HOARDING_SETGAME_H
#include <vector>
#include <memory>
#include "Property.h"
using std::vector;
using std::shared_ptr;
namespace Monopoly {
void gameSet(char **argv, int numOfPlayer, Board &map, vector<Player> &playerGroup, Gamestate &gamestate);
}
#endif
