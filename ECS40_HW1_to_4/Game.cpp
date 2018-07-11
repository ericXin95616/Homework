//
// Created by xinbochao on 18-1-13.
//
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

namespace Monopoly {
/*check if game ends
 * Game ends in two different ways
 * First, the number of Player existing is less than "endNumOfPlayer"
 * Second, countTurn is equal to turnlimit
 * (if turnLimit == -1, the second situation will never happen)
 */
bool isGameEnd(vector<Player> &playerGroup, Gamestate &gamestate) {
  return gamestate.isReachTurnLimit() || (static_cast<int>(playerGroup.size()) <= playerGroup[0].getEndNumOfPlayer());
}

/* Print all winners' name
 * if multiple winners exist, it will print one winner's name in one line
 */
void printWinner(vector<Player> &playerGroup) {
  cout << "The winners are" << endl;
  vector<vector<Player>::iterator > winners;
  auto it = playerGroup.begin();
  while(it != playerGroup.end() ) {
    auto itToWinner = std::max_element(it, playerGroup.end());
    if(winners.empty() || !(*itToWinner < *winners.back())) {
      winners.push_back(itToWinner);
      it = ++itToWinner;
    }
    else
      break;
  }
  std::for_each(winners.begin(), winners.end(), [](auto element){cout << element->getPlayerName() << endl; });
}

void displayPlayers(const vector<Player> &playerGroup, const ptrToPlace& place) {
  //This variable is used to indicate whether this Space has multiple players
  bool isMultiplePlayer = false;
  for (unsigned int j = 0; j < playerGroup.size(); ++j) {
    if (playerGroup.at(j).getWhere() == place->getName()) {
      if (!isMultiplePlayer) {
        cout << playerGroup.at(j).toString();
        isMultiplePlayer = true;
      } else {
        cout << ", " << playerGroup.at(j).toString();
      }
    }
  }
  cout << endl;
}

void displayMap(const vector<Player> &playerGroup, const Board &map) {

  size_t maxLenOfPlaceName, maxLenOfPlayerName, maxLenOfUpgrades;
  map.at(0)->getMaxLens(maxLenOfPlaceName, maxLenOfPlayerName, maxLenOfUpgrades);
  //we print the first line of the map
  cout << "Space Number" << " | "
       << std::setw(maxLenOfPlaceName) << std::left << "Space Name" << " | "
       << std::setw(maxLenOfPlayerName) << std::left << "Owner" << " | "
       << std::setw(maxLenOfUpgrades) << std::left << "Upgrades" << " | " << "Players" << endl;

  for (auto it = map.cbegin(), end = map.cend(); it != end; ++it) {
    (*it)->display();
    displayPlayers(playerGroup, *it);
  }
}

/*
 * This function will be fucking large(200+ lines combined)
 * so I will declare all the auxiliary functions I used before this comment
 * Basically this function do the following work:
 * First, display the map (include where all the players are)
 * Two choice: (will not enter the second part if Player not choose action 1)
 * 1, Roll the dice (Reading Random number from fpRandom)
 * 2, Leave the game (its asset will be set to 0.0 and thus being remove from this game)
 *
 * After rolling the dice:
 * first, print the result of the action (If Player choose to leave the game or bankrupt
 * , his turn ends here, erase that Player from playerGroup)
 * second, print the updating map (Player's location change)
 */

bool rollDice(Player &butner, Board &map, DiceRoller &dice);
void leaveGame(vector<Player> &playerGroup, const unsigned int index);
int firstAction(vector<Player> &playerGroup, Board &map, const unsigned int index);

/*
 * the return value and the bool input use to indicate if
 * someone leave game last turn
 */
bool playerTurn(vector<Player> &playerGroup, Board &map, unsigned int &playerIndex, bool someoneLeave) {
  /*
   * Personally, I don't like this part of code
   * but I can't solve this problem in more elegant way
   */
  if (!someoneLeave) {
    if (playerIndex == playerGroup.size() - 1)
      playerIndex = 0;
    else ++playerIndex;
  } else {
    if (playerIndex > playerGroup.size() - 1)
      playerIndex = 0;
  }

  //this indicates that Player choose to leave the game, we return the control to the main
  if (firstAction(playerGroup, map, playerIndex) == 4)
    return true;
  return false;
}

int firstAction(vector<Player> &playerGroup, Board &map, const unsigned int index) {
  if(playerGroup.at(index).isInJail()) {
    //while player in jail returns false if player bankrupts
    if(!playerGroup.at(index).whilePlayerInJail()){
      leaveGame(playerGroup, index);
      map.setPtrToPlayerGroup(&playerGroup);
      //which indicates that player leaves the game
      displayMap(playerGroup, map);
      return 4;
    }
  }
  label:
  int playerAction = 0;
  cout << playerGroup.at(index).getPlayerName() << " " << "please enter your move" << endl;
  cout << "1 to roll dice" << endl
       << "2 to upgrade a property with a house or hotel" << endl
       << "3 to sell a house or hotel" << endl
       << "4 to leave the game" << endl
       << "Your move: ";
  cin >> playerAction;
  switch (playerAction) {
    case 1: {
      //RollDice returns true if roll double && player still exists
      if(playerGroup.at(index).RollDice(map.begin(), map.end())) {
        displayMap(playerGroup, map);
        goto label;
      }

      if(!playerGroup.at(index).isPlayerExist()) {
        leaveGame(playerGroup, index);
        map.setPtrToPlayerGroup(&playerGroup);
        playerAction = 4;
      } else {
        playerGroup.at(index).endTurn();
      }
      break;
    }
    case 2: playerGroup.at(index).upgradeProperty(); displayMap(playerGroup, map); goto label;
    case 3: playerGroup.at(index).sellUpgrade(); displayMap(playerGroup, map); goto label;
    case 4: leaveGame(playerGroup, index); map.setPtrToPlayerGroup(&playerGroup);break;
    default: cout << "In move_number_to_move something terrible happened when converting the move number" << endl;
  }
  displayMap(playerGroup, map);
  return playerAction;
}

bool rollDice(Player &butner, Board &map, DiceRoller &dice) {
  int randomNumer = dice.RollDice();
  cout << butner.getPlayerName() << ", you rolled a " << randomNumer << "\n";
  butner.moveForward(randomNumer, map.begin(), map.end());
  return butner.isPlayerExist();
}

/*
 * erase a Player from playerGroup
 * remember if someone leave the game
 * it means all his Property will be
 * return to no one and thus other can
 * buy it again
 */
void leaveGame(vector<Player> &playerGroup, const unsigned int index) {
  vector<Player>::iterator it = playerGroup.begin() + index;
  it->endTurn();
  it->returnProperty();
  playerGroup.erase(it);

  /*
   * Once we erase an element from the playerGroup, we change the address of
   * all other player, which means that the owner pointer in the property will
   * point to previous address. Therefore, after each erase, we update properties'
   * owner pointer
   */
  for (auto it = playerGroup.begin(), end = playerGroup.end(); it != end; ++it) {
    (*it).resetOwner();
  }
}
}





