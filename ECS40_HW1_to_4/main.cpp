//
// Created by xinbochao on 18-1-13.
//
#include "Property.h"
#include "setGame.h"
#include "Game.h"
#include <iostream>

using std::vector;
using std::cout;
using std::cin;
using std::cout;
using std::endl;
using namespace Monopoly;

int main(int argc, char* argv[]) {
  if(argc != 4) {
    cout << "Do not have enough command line arguments!" << endl;
    cout << "Program ends!" << endl;
    return 0;
  }

  Board map;
  vector<Player> playerGroup;
  Gamestate gameState;
  int numOfPlayer = 0;

  cout << "Enter how many players will be playing: ";
  cin >> numOfPlayer;

  gameSet(argv, numOfPlayer, map, playerGroup, gameState);

  displayMap(playerGroup, map);
  unsigned int playerIndex = 0;
  bool isSomeoneLeave = true;
  while(!isGameEnd(playerGroup, gameState)) {
    isSomeoneLeave = playerTurn(playerGroup, map, playerIndex, isSomeoneLeave);
  }

  printWinner(playerGroup);
}
