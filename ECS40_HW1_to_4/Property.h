#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <vector>
#include <memory>
#include <set>
#include "rules.h"
#include "OtherClass.h"

using std::string;
using std::vector;
using std::set;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

namespace  Monopoly {
class Player;
class Rules;
class Property;
class Space;
class DiceRoller;

typedef shared_ptr<vector<unsigned int> > ptrToPPS;
typedef Property* ptrToProperty;
typedef unique_ptr<Space> ptrToPlace;
typedef shared_ptr<Rules> ptrToRules;
typedef shared_ptr<DiceRoller> ptrToDice;
/*
 * Space is an abstract base class
 */
class Space {
 public:
  Space(shared_ptr<Rules> _rules, const string &name): rules(_rules), name(name){}
  virtual ~Space() {}
  virtual void activate(Player &_player) = 0; // Player class
  virtual void setPlayerGroupPtr(vector<Player> *ptr)=0;
  virtual void display() const;

  string getName() const {return name;};
  void setMaxLens(size_t place, size_t player, size_t upgrades);
  void setSpaceNumber(int space){spaceNumber = space;}
  void getMaxLens(size_t &place, size_t &player, size_t &upgrades) const;

 protected:
    ptrToRules rules;
    string name;
    size_t maxLenOfPlaceName;
    size_t maxLenOfPlayerName;
    size_t maxLenOfUpgrades;
    int spaceNumber;
};

//Property Class
class Property : public Space {
 public:
  Property() = default;
  Property(int _setID, int _intrasetID, const string &_Name, double _cost,
           double _houseCost, double _hotelCost, double _rent, double _rentHouse,
           double _rentHotel, const ptrToRules &_rules);

  int upgradeProperty();
  int upgradeMoney()const;
  int downgradeProperty();
  int downgradeMoney() const ;
  void resetUpgrades() {houseNum = 0; hotel = false;}
  void setOwner(Player *_owner = nullptr) { owner = _owner; }
  void setPlayerGroupPtr(vector<Player> *ptr) {ptrTOPlayerGroup = ptr;}
  void auction();
  int countAuctionablePlayer()const;
  double rentPrice();
  void display()const override;
  void activate(Player &_player) override;
  double getCost() const { return cost; }

  int getSetID() const { return setID; }
  int getIntrasetID() const { return intrasetID; }
  double getHouseCost() const { return houseCost; }
  double getHotelCost() const { return hotelCost; }
  bool isHotelExist() const {return hotel; }
  int getHouseNum() const {return houseNum;}
  //this operator is meant for set to order the property player has
  bool operator<(const Property &_Property) const ;
  int netWorthOfUpgrades()const ;

 private:
  const int setID;
  const int intrasetID;
  const double cost; //cost to buy that Property
  const double houseCost; // cost to build a single house
  const double hotelCost; // cost to upgrade house to hotel
  const double rent; // money need to pay if someone land this Property(no need to pay if no one own it)
  const double rentHouse; // money need to pay after building house
  const double rentHotel; // money nned to pay after building hotel
  Player *owner; //Player &owner
  int houseNum;
  bool hotel;
  vector<Player> *ptrTOPlayerGroup;// this variable is need for enable auction function
};

class Go : public Space {
 public:
  Go() = default;
  Go(double _moneyCollect, const string &name, const ptrToRules &_rules)
      : Space(_rules, name), moneyCollect(_moneyCollect) {}
  void activate(Player &_player) override ;
  double getMoney() const { return moneyCollect; } //this func is called when a player passes the go place
  void setPlayerGroupPtr(vector<Player> *ptr) override {}

 private:
  const double moneyCollect;
};

class Free_Parking : public Space{
 public:
  Free_Parking(const ptrToRules& rules, const string& name, const shared_ptr<int>& money)
      : Space(rules, name), money(money){}
  void activate(Player& _player)override;
  void setPlayerGroupPtr(vector<Player> *ptr) override {}

 private:
  shared_ptr<int> money;
};

class Pay_Bank : public  Space{
 public:
  Pay_Bank(const ptrToRules& rules, const string& name, const shared_ptr<int>& money, int paidMoney):
      Space(rules, name), paidMoney(paidMoney), moneyInFreeParking(money){}
  void activate(Player& _player)override;
  void setPlayerGroupPtr(vector<Player> *ptr) override {}

 private:
  int paidMoney;
  shared_ptr<int> moneyInFreeParking;
};

class Jail : public Space{
 public:
  Jail(const ptrToRules& rules, const string& name, int maxNumOfTurns, int moneyNeedToPay, shared_ptr<int>& money):
      Space(rules, name), maxNumOfTurns(maxNumOfTurns), moneyNeedToPay(moneyNeedToPay), moneyInFreeParking(money){}
  void activate(Player& _player)override;
  void setPlayerGroupPtr(vector<Player> *ptr) override {}
  int getMaxNumOfTurns()const {return maxNumOfTurns;}
  int getMoneyNeedToPay()const {return moneyNeedToPay;}

 private:
  int maxNumOfTurns;
  int moneyNeedToPay;
  shared_ptr<int> moneyInFreeParking;
};

class GoToJail : public Space{
 public:
  GoToJail(const ptrToRules& rules, const string& name, int indexOfJail):
      Space(rules, name), indexOfJail(indexOfJail){}
  void setJailIterator(vector<ptrToPlace>::iterator &begin){jailPlace = begin + indexOfJail;}
  void activate(Player& _player) override;
  void setPlayerGroupPtr(vector<Player> *ptr) override {}

 private:
  int indexOfJail;
  vector<ptrToPlace>::iterator jailPlace;
};


class Player {
  //static bool comp(ptrToProperty p1, ptrToProperty p2) {return *p1 < *p2; }
 public:
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
  vector<ptrToProperty> whichPropertyUpgradeable(bool buildEvenly) const;
  vector<ptrToProperty> whichPropertyDowngradeable(bool buildEvenly) const;

  void setPlayerPlace(vector<ptrToPlace>::iterator& _it){it = _it;}
  void setJail(Jail *_jail){jail = _jail; numOfTurnLeftInJail = (jail)?jail->getMaxNumOfTurns()+1:0;}
  int getNumOfTurnLeftInJail()const {return numOfTurnLeftInJail;}
  bool isInJail()const {return jail != nullptr;}
  int getJailPayment()const {return jail->getMoneyNeedToPay();}
  bool whilePlayerInJail() {jail->activate(*this); return this->isPlayerExist(); }

  void propertyToOther(Player &_player);
  void returnProperty();
  void resetOwner();
  void setAuction(bool value) {isAuction = value;}
  bool RollDice(vector<ptrToPlace>::iterator begin, vector<ptrToPlace>::iterator end);
  void endTurn();
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

  int netWorthOfProperty()const;
  bool operator<(const Player &butner)const;

 private:
  unsigned int playerID;
  string playerName;
  double asset;//how much money your own, if asset == 0, it means that this Player has bankrupt and will be removed from this game
  bool isAuction;
  vector<ptrToProperty > ownedProperty;//the Property Player own
  ptrToPPS propertyPerSet;
  vector<ptrToPlace>::iterator it;//indicate where Player is in the map(vector)
  ptrToRules rules;
  ptrToDice Dice;
  int numOfTurnLeftInJail;
  Jail* jail;
};
}
#endif










