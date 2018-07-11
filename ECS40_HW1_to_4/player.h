#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
#include "rules.h"
#include "OtherClass.h"
#include <vector>
#include <memory>
#include <string>
#include <set>

using std::vector;
using std::set;
using std::string;
using std::shared_ptr;

namespace Monopoly{
class Player {
  static bool comp(ptrToProperty p1, ptrToProperty p2) {return *p1 < *p2; }
 public:
  typedef shared_ptr<vector<unsigned int> > ptrToPPS;
  typedef Property* ptrToProperty;
  typedef shared_ptr<Space> ptrToPlace;
  typedef shared_ptr<Rules> ptrToRules;
  typedef shared_ptr<DiceRoller> ptrToDice;

  Player() = default;
  Player(const unsigned int _playerID,
         const string &_playerName,
         const double &initialAsset,
         vector<ptrToPlace>::iterator _it,
         const ptrToPPS &_propertyPerSet,
         const ptrToRules &_rules,
         const ptrToDice &_Dice
         );

  bool isPlayerExist() const { return asset != -1.0; }
  bool canBuy() { return (asset >= (*it)->getCost()); } //if someone owns it, we will not use this function
  bool isOwnAllSet(const Property &_Property) const;
  bool isAuctionAble()const {return isAuction;}

  double assetChange(const double changedMoney);
  void moveForward(const int numForward,
                   vector<ptrToPlace>::iterator begin,
                   vector<ptrToPlace>::iterator end); //effectToPlayer
  void buyProperty(Property &_Property, int cost);
  void addProperty(Property &_Property);
  void upgradeProperty();
  void sellUpgrade();
  void sellUpgradeToAvoidBankrupt(int rentMoney);
  bool anyPropertyUpgradeable()const;
  bool anyPropertyDowngradeable() const;
  auto whichPropertyUpgradeable(bool buildEvenly) const;
  auto whichPropertyDowngradeable(bool buildEvenly) const;
  void propertyToOther(Player &_player);
  void returnProperty();
  void resetOwner();
  void setAuction(bool value) {isAuction = value;}
  bool RollDice(vector<ptrToPlace>::iterator begin, vector<ptrToPlace>::iterator end);
  void endTurn() { rules->endTurn(); }
  int lowestNumberInOneSet(int setID) const;
  int highestNumberInOneSet(int setID) const;
  string toString() const;

  int getEndNumOfPlayer() const { return rules->getEndOfPlayer(); }
  string getPlayerID() const { return "Player " + std::to_string(playerID); }
  unsigned int getIntID() const { return playerID; }
  double getAsset() const { return asset; }
  string getPlayerName() const { return playerName; }
  string getWhere() const { return (*it)->getName(); }
  int getThresholdHouseNum() const {return rules->getThresholdHouseNum(); }

 private:
  unsigned int playerID;
  string playerName;
  double asset;//how much money your own, if asset == 0, it means that this Player has bankrupt and will be removed from this game
  bool isAuction;
  set<ptrToProperty, decltype(comp)*> ownedProperty{comp};//the Property Player own
  ptrToPPS propertyPerSet;
  vector<ptrToPlace>::iterator it;//indicate where Player is in the map(vector)
  ptrToRules rules;
  ptrToDice Dice;
};
}
#endif
