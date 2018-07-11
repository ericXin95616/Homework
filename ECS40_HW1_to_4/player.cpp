#include "player.h"

using namespace Monopoly;
//Class Player:
Player::Player(const unsigned int _playerID,
               const string &_playerName,
               const double &initialAsset,
               vector<ptrToPlace>::iterator _it,
       const ptrToPPS &_propertyPerSet,
       const ptrToRules &_rules,
               const ptrToDice &_Dice
)
    : playerID(_playerID), playerName(_playerName), asset(initialAsset), propertyPerSet(_propertyPerSet),
      it(_it),  rules(_rules), Dice(_Dice){}

bool Player::isOwnAllSet(const Property &_Property)const{
  assert(ownedProperty.size() > 0 && propertyPerSet->size() > 0);
  int setIndex = _Property.getSetID();
  unsigned int numOfProperty = 0;
  for(auto it = ownedProperty.cbegin(), end = ownedProperty.cend(); it != end; ++it) {
    if((*it)->getSetID() == setIndex)
      ++numOfProperty;
  }
  return numOfProperty == propertyPerSet->at(setIndex);
}

/*
 * asset change by the value input
 * if Player losing money, the input value should be < 0
 * if Player bankrupt(asset <= 0), this function will return
 * all the asset Player has, and set his asset to 0.0
 * other time, this function return a value that is equal to absolute
 * value of changedMoney
 */
double Player::assetChange(const double changedMoney) {
  //do I need to use abs(asset - 0.0) < thresholdNum here?
  if( asset + changedMoney < 0.0 ) {
    double assetNum = asset;
    asset = -1.0;
    return assetNum;
  }
  asset += changedMoney;
  return abs(changedMoney);
}

/*
 * This function mimic the behavior that token being moved in the map
 * If pass the go, remember to collect money
 * If landing on somewhere, remember to call the virtual function effectToPlayer
 */
void Player::moveForward(const int numForward, vector<ptrToPlace>::iterator begin, vector<ptrToPlace>::iterator end) {
  for (int i = 0; i < numForward; ++i) {
    ++it;
    //we first judge if it == end, because we want to make sure that it can be deferenced
    if(it == end){
      it = begin;
    }
    //we then judge if Player pass(!) the go
    if( i != numForward - 1 && !(*it)->isProperty()){
      (*it)->effectToPlayer(*this, true);
    }
  }
  //we then want to know what the landing effect is
  //isSomeoneOwn tells us if other Player owns all the properties of this set
  if((*it)->isProperty())
    (*it)->effectToPlayer(*this, (*it)->isSomeoneOwn());
  else
    (*it)->effectToPlayer(*this, false);
}

void Player::buyProperty(Property &_Property, int cost) {
  this->assetChange(-cost);
  this->addProperty(_Property);
}

void Player::addProperty(Property &_Property) {
  this->ownedProperty.insert(&_Property);
  _Property.setOwner(this);
  //std::sort(ownedProperty.begin(), ownedProperty.end(), [](auto lhs, auto rhs){return *lhs < *rhs;});
}

/*
 * transfer all the Property to other Player
 */
void Player::propertyToOther(Player &_player) {
  //assert(this->isPlayerExist() == false);
  while(!ownedProperty.empty()) {
    for(auto it = ownedProperty.begin(); it != ownedProperty.end(); ++it) {
      _player.addProperty(*(*it));
    }
    ownedProperty.clear();
  }
}


bool Player::anyPropertyDowngradeable() const {
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if((*it)->getHouseNum() > 0)
      return true;
  }
  return false;
}

auto Player::whichPropertyDowngradeable(bool buildEvenly) const {
  set<ptrToProperty, decltype(comp)*> propertyDowngradeable{comp};
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    int numOfUpgrades = (*it)->getHouseNum() + (*it)->isHotelExist();
    if(!buildEvenly) {
      if(numOfUpgrades > 0)
        propertyDowngradeable.insert(*it);
    } else {
      if(numOfUpgrades > 0 && numOfUpgrades == highestNumberInOneSet((*it)->getSetID()))
        propertyDowngradeable.insert(*it);
    }
  }
  return propertyDowngradeable;
}

int Player::highestNumberInOneSet(int setID) const {
  int highestUpgrades = 0;
  bool isFirstProperty = true;
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if((*it)->getSetID() != setID)
      continue;
    if(isFirstProperty) {
      highestUpgrades = (*it)->getHouseNum() + (*it)->isHotelExist();
      isFirstProperty = false;
    } else {
      int upgradesNum = (*it)->getHouseNum() + (*it)->isHotelExist();
      highestUpgrades = (upgradesNum > highestUpgrades) ? upgradesNum : highestUpgrades;
    }
  }
  return highestUpgrades;
}

bool Player::anyPropertyUpgradeable()const {
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if(this->isOwnAllSet(*(*it)) && this->asset >= (*it)->upgradeMoney() && !(*it)->isHotelExist())
      return true;
  }
  return false;
}

auto Player::whichPropertyUpgradeable(bool buildEvenly)const{
  set<ptrToProperty, decltype(comp)*> propertyUpgradeable{comp};
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if(!buildEvenly) {
      if (this->isOwnAllSet(*(*it)) && this->asset >= (*it)->upgradeMoney() && !(*it)->isHotelExist())
        propertyUpgradeable.insert(*it);
    } else {
      if(this->isOwnAllSet(*(*it)) && this->asset >= (*it)->upgradeMoney() && !(*it)->isHotelExist()
          && (*it)->getHouseNum() == lowestNumberInOneSet((*it)->getSetID()))
        propertyUpgradeable.insert(*it);
    }
  }
  return propertyUpgradeable;
}

int Player::lowestNumberInOneSet(int setID) const {
  int lowestHouseNum = 0;
  bool isFirstProperty = true;
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if((*it)->getSetID() != setID)
      continue;
    if(isFirstProperty) {
      lowestHouseNum = (*it)->getHouseNum();
      isFirstProperty = false;
    } else {
      lowestHouseNum = ((*it)->getHouseNum() < lowestHouseNum) ? (*it)->getHouseNum() : lowestHouseNum;
    }
  }
  return lowestHouseNum;
}

void Player::sellUpgradeToAvoidBankrupt(int rentMoney) {
  auto propertyDowngradeable = this->whichPropertyDowngradeable(rules->isBuildEvenly());
  cout << "You have $" << static_cast<int>(this->asset) << " but you owe $" << rentMoney << endl;
  cout << "Pick an upgrade to sell to make up the difference" << endl;
  int count = 0;
  for(auto it = propertyDowngradeable.begin(), end = propertyDowngradeable.end(); it != end; ++it) {
    cout << count << ". " << (*it)->getName() << " [$" << (*it)->downgradeMoney() << "]" << endl;
    ++count;
  }
  cout << "Your choice: ";
  int userChoice = 0;
  cin >> userChoice;
  auto it = propertyDowngradeable.begin();
  for(int i = 0; i < userChoice; ++i)
    ++it;
  ptrToProperty downgradeProperty = *it;
  this->assetChange(downgradeProperty->downgradeProperty());
}

void Player::sellUpgrade(){
  if(!this->anyPropertyDowngradeable()){
    cout << "You don't have any upgrades that you can sell" << endl;
    return;
  }

  auto propertyDowngradeable = whichPropertyDowngradeable(rules->isBuildEvenly());
  cout << "Which property do you want to downgrade?" << endl;
  int count = 0;
  for(auto it = propertyDowngradeable.begin(), end = propertyDowngradeable.end(); it != end; ++it){
    cout << count << ". " << (*it)->getName() << " [$" << (*it)->downgradeMoney() << "]" << endl;
    ++count;
  }
  cout << "Your choice: ";
  int playerChoice = 0;
  cin >> playerChoice;

  auto it = propertyDowngradeable.begin();
  for(int i = 0; i < playerChoice; ++i)
    ++it;
  ptrToProperty downgradeProperty = *it;
  this->assetChange(downgradeProperty->downgradeProperty());
}

void Player::upgradeProperty() {
  if(!this->anyPropertyUpgradeable()) {
    cout << "You don't have any properties that you can upgrade" << endl;
    return;
  }
  auto propertyUpgradeable = whichPropertyUpgradeable(rules->isBuildEvenly());
  cout << "Which property do you want to upgrade?" << endl;
  int count = 0;
  for(auto it = propertyUpgradeable.begin(), end = propertyUpgradeable.end(); it != end; ++it){
    cout << count << ". " << (*it)->getName() << " [$" << (*it)->upgradeMoney() << "]" << endl;
    ++count;
  }
  cout << "Your choice: ";
  int playerChoice = 0;
  cin >> playerChoice;
  /*
   * we bring the property that player choose
   */
  auto it = propertyUpgradeable.begin();
  for(int i = 0; i < playerChoice; ++i)
    ++it;
  ptrToProperty upgradeProperty = *it;
  this->assetChange(-(upgradeProperty->upgradeProperty()));
}


void Player::resetOwner() {
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    (*it)->setOwner(this);
  }
  //ownedProperty.clear();
}

bool Player::RollDice(vector<ptrToPlace>::iterator begin, vector<ptrToPlace>::iterator end) {
  int randomNum = Dice->RollDice();
  cout << this->getPlayerName() << ", you rolled a " << randomNum << "\n";
  this->moveForward(randomNum, begin, end);
  if(!this->isPlayerExist() || !Dice->canRollAgain(rules->getMaxDoubleLimit())) {
    Dice->resetCount();
    return false;
  }
  return true;
}

/*
 * return all properties to no one
 */
void Player::returnProperty(){
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    (*it)->setOwner();
    (*it)->resetUpgrades();
  }
}

string Player::toString() const {
  string temp;
  return temp + "[" + this->playerName + " : " + "$" + std::to_string(static_cast<int>(this->asset)) + "]";
}
