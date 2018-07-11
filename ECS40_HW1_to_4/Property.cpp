#include "Property.h"
#include <iostream>
#include <assert.h>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;

using namespace Monopoly;
//Space class
void Space::setMaxLens(size_t place, size_t player, size_t upgrades) {
  this->maxLenOfPlaceName = place;
  this->maxLenOfPlayerName = player;
  this->maxLenOfUpgrades = upgrades;
}

void Space::display() const {
  cout << std::setw(12) << std::left << spaceNumber << " | "
       << std::setw(maxLenOfPlaceName) << std::left << this->getName() << " | "
       << std::setw(maxLenOfPlayerName) << std::left << "None" << " | "
       << std::setw(maxLenOfUpgrades) << std::left << string() << " | ";
}

void Space::getMaxLens(size_t &place, size_t &player, size_t &upgrades) const {
  place = maxLenOfUpgrades;
  player = maxLenOfPlayerName;
  upgrades = maxLenOfUpgrades;
}
// Property class
void Property::display() const {
  cout << std::setw(12) << std::left << spaceNumber << " | "
       << std::setw(maxLenOfPlaceName) << std::left << this->getName() << " | ";

  if(owner == nullptr)
    cout << std::setw(maxLenOfPlayerName) << std::left << "None" << " | ";
  else
    cout << std::setw(maxLenOfPlayerName) << std::left << owner->getPlayerName() << " | ";

  if(hotel)
    cout << std::setw(maxLenOfUpgrades) << std::left << "H" << " | ";
  else
    cout << std::setw(maxLenOfUpgrades) << std::left << string(houseNum, 'h') << " | ";
}

Property::Property(int _setID, int _intrasetID, const string &_Name, double _cost,
         double _houseCost, double _hotelCost, double _rent, double _rentHouse,
         double _rentHotel, const ptrToRules &_rules) : Space(_rules, _Name),
                                                        setID(_setID),
                                                        intrasetID(_intrasetID),
                                                        cost(_cost),
                                                        houseCost(_houseCost),
                                                        hotelCost(_hotelCost),
                                                        rent(_rent),
                                                        rentHouse(_rentHouse),
                                                        rentHotel(_rentHotel) {
  houseNum = 0;
  hotel = false;
  owner = nullptr;
}
/*
int Property::addHouse(int addNum) {
	houseNum += addNum;
	return houseNum;
}
// Need improve
bool Property::upgradeHotel() {
	return false;
}
*/
/*
 * we upgrade property by one
 * return the money it cost
 */
int Property::upgradeProperty() {
  int upgrade = upgradeMoney();
  if(houseNum == rules->getThresholdHouseNum())
    hotel = true;
  else
    ++houseNum;
  return upgrade;
}

int Property::upgradeMoney() const {
  if(houseNum == rules->getThresholdHouseNum())
    return static_cast<int>(this->hotelCost);
  return static_cast<int>(this->houseCost);
}

int Property::downgradeProperty() {
  int downgrade = downgradeMoney();
  if(hotel)
    hotel = false;
  else
    --houseNum;
  return downgrade;
}

/*
 * Personally, I think it should be divided by 2
 */
int Property::downgradeMoney() const {
  if(hotel)
    return static_cast<int>(hotelCost) / 2;
  return static_cast<int>(houseCost) / 2;
}
/*
 * this function returns the number of money
 * that needed for landing on this Property
 * Remember to judge whether the owner has all
 * the properties of this set
 */
double Property::rentPrice() {
  assert(owner != nullptr);
  bool ownAllSet = owner->isOwnAllSet(*this);
  
  if(hotel)
    return rentHotel;
	
  if(houseNum)
    return rentHouse * pow(2, houseNum - 1);

  return rent + ownAllSet * (rules->getSetMultiply() - 1) * rent;
}

/*
 * the name of parameter is a little confusing
 * but isOwned here has a different meaning
 * it use to indicates whether other Player owns this Property
 * Remember to judge if someone owns the whole set!!!
 */
void Property::activate(Player &_player) {
  //no one owns it, offer Player a chance to buy it (only if he has enough money)
  bool isOwned = (this->owner != nullptr);
  if(!isOwned) {
    //judge if player has enough money to buy it
    if(_player.getAsset() >= this->getCost()) {
      cout << "Would you like to buy " << this->name
           << " for $" << (int)this->cost << "?\n";
      /*
       * if the Player currently own all other properties in this set
       * and this purchase will make his rent multiplies with Property set multiplier
       * should we print the original rent or the rent after multiplication ???
       */
      cout << "Rent on " << this->name << " is $" << (int)this->rent << endl;
      cout << "Enter y for yes or n for no: ";
      char answer;
      cin >> answer;
      if(toupper(answer) == 'Y') {
        _player.buyProperty(*this, static_cast<int>(this->getCost()) );
        cout << _player.getPlayerName() << " bought " << this->name << " for $" << static_cast<int>(this->cost) << endl;
      }else {
        if(rules->isAuctionAllow())
          this->auction();
      }
    } else {
      cout << _player.getPlayerName() << ", you don't have enough money to afford " << this->name << ". "
           << this->name << " costs $" << (int)this->cost << " but you only have $" <<(int)_player.getAsset() << endl;
      if(rules->isAuctionAllow())
        this->auction();
    }
    return;
  }

  //owner is yourself, nothing happens
  if(owner->getPlayerID() == _player.getPlayerID()) {
    cout << _player.getPlayerName() << ", you landed on " << this->name << " which you already own" << endl;
    return;
  }

  /*
   * someone else owns this Property
   * first we need to judge how much money Player will lost
   * and set his asset to 0
   */
  double rentMoney = this->rentPrice();

  while(_player.getAsset() < rentMoney && _player.anyPropertyDowngradeable()) {
    _player.sellUpgradeToAvoidBankrupt(rentMoney);
  }

  double moneyReceive = _player.assetChange(-rentMoney);
  owner->assetChange(moneyReceive);
  //this indicates that Player has bankrupt
  if(!_player.isPlayerExist()) {
    _player.propertyToOther(*owner);
    cout << _player.getPlayerName() << " went bankrupt to " << owner->getPlayerName() << " for landing on " << this->name << endl;
  } else {
    cout << _player.getPlayerName() << " paid " << owner->getPlayerName() << " $" << (int)moneyReceive
         << " for landing on " << this->name << endl;
  }
}

void Property::auction() {
  int highestBid = 0;
  Player *highestBider = nullptr;

  cout << "Starting the auction for " << this->getName() << endl;
  for(auto it = ptrTOPlayerGroup->begin(); it != ptrTOPlayerGroup->end(); ++it) {
    it->setAuction((it->getAsset() >= 1.0));
  }

  int auctionablePlayer = this->countAuctionablePlayer();
  while(auctionablePlayer >= 1) {
    for (auto it = ptrTOPlayerGroup->begin(); it != ptrTOPlayerGroup->end(); ++it) {
      if(!it->isAuctionAble())
        continue;
      if(static_cast<int>(it->getAsset()) < highestBid + 1) {
        it->setAuction(false);
        --auctionablePlayer;
        /*
         * if someone's bid is higher than others' cash
         * then auction ends
         */
        if(auctionablePlayer <= 1)
          break;
        continue;
      }
      int bid = 0;
      if(highestBider == nullptr) {
        cout << "No one has bid on " << this->getName() << " [$ " << this->cost << "] yet" << endl;
      } else {
        cout << "The current bid for "<< this->getName() << " [$ "<< this->cost << "] is $"
             << highestBid << " by " << highestBider->getPlayerName() << endl;
      }

      cout << it->getPlayerName() << ", enter a bid of at least $"<< highestBid + 1
           << " to bid on the property or a value less than that to leave the auction" << endl;
      cout << "Your bid: ";
      cin >> bid;
      if(bid < highestBid + 1) {
        it->setAuction(false);
        --auctionablePlayer;
      } else {
        highestBid = bid;
        highestBider = &(*it);
      }
      /*
       * Auction ends if all people decide to quit the auction
       * or one people has bid and no other decide to bid
       */
      if((auctionablePlayer == 1 && highestBider != nullptr) || auctionablePlayer == 0)
        break;
    }
    if(auctionablePlayer <= 1)
      break;
  }
  //declare who win the bid
  if(highestBider == nullptr)
    cout << "No one decided to purchase " << this->getName() << endl;
  else {
    cout << highestBider->getPlayerName() << " won " << this->getName() << " for $" << highestBid << endl;
    highestBider->buyProperty(*this, highestBid);
  }
}

int Property::countAuctionablePlayer()const {
  int count = 0;
  for(auto it = ptrTOPlayerGroup->begin(); it != ptrTOPlayerGroup->end(); ++it) {
    count += it->isAuctionAble();
  }
  return count;
}
/*
 * this function only aims to support associative container set<Property> in player class
 */
bool Property::operator<(const Property &_Property) const {
  return (this->setID < _Property.setID) || (this->setID == _Property.setID && this->intrasetID < _Property.intrasetID);
}

int Property::netWorthOfUpgrades() const {
  return static_cast<int>(cost + houseCost * houseNum + hotelCost*hotel);
}


//Go class
void Go::activate(Player &_player) {
	double moneyToPlayer = moneyCollect + (rules->getSalaryMultiply() - 1) * moneyCollect;
    _player.assetChange(moneyToPlayer);
}


		
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
      it(_it),  rules(_rules), Dice(_Dice), numOfTurnLeftInJail(0), jail(nullptr){}

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
    Go* isGo = dynamic_cast<Go*>(it->get());
    if( i != numForward - 1 && isGo ){
      this->assetChange(isGo->getMoney());
    }
  }
  //we then want to know what the landing effect is
  //isSomeoneOwn tells us if other Player owns all the properties of this set
  (*it)->activate(*this);
}

void Player::buyProperty(Property &_Property, int cost) {
  this->assetChange(-cost);
  this->addProperty(_Property);
}

void Player::addProperty(Property &_Property) {
  this->ownedProperty.push_back(&_Property);
  _Property.setOwner(this);
  std::sort(ownedProperty.begin(), ownedProperty.end(), [](auto lhs, auto rhs){return *lhs < *rhs;});
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
void Player::upgradeProperty() {
  if(!this->anyPropertyUpgradeable()) {
    cout << "You don't have any properties that you can upgrade" << endl;
    return;
  }
  vector<ptrToProperty> propertyUpgradeable = whichPropertyUpgradeable(rules->isBuildEvenly());
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

void Player::sellUpgrade(){
  if(!this->anyPropertyDowngradeable()){
    cout << "You don't have any upgrades that you can sell" << endl;
    return;
  }

  vector<ptrToProperty> propertyDowngradeable = whichPropertyDowngradeable(rules->isBuildEvenly());
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


void Player::sellUpgradeToAvoidBankrupt(int rentMoney) {
  vector<ptrToProperty> propertyDowngradeable = this->whichPropertyDowngradeable(rules->isBuildEvenly());
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

bool Player::anyPropertyDowngradeable() const {
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if((*it)->getHouseNum() > 0)
      return true;
  }
  return false;
}

vector<ptrToProperty> Player::whichPropertyDowngradeable(bool buildEvenly) const {
  vector<ptrToProperty> propertyDowngradeable;
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    int numOfUpgrades = (*it)->getHouseNum() + (*it)->isHotelExist();
    if(!buildEvenly) {
      if(numOfUpgrades > 0)
        propertyDowngradeable.push_back(*it);
    } else {
      if(numOfUpgrades > 0 && numOfUpgrades == highestNumberInOneSet((*it)->getSetID()))
        propertyDowngradeable.push_back(*it);
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

vector<ptrToProperty> Player::whichPropertyUpgradeable(bool buildEvenly)const{
  vector<ptrToProperty> propertyUpgradeable;
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    if(!buildEvenly) {
      if (this->isOwnAllSet(*(*it)) && this->asset >= (*it)->upgradeMoney() && !(*it)->isHotelExist())
        propertyUpgradeable.push_back(*it);
    } else {
      if(this->isOwnAllSet(*(*it)) && this->asset >= (*it)->upgradeMoney() && !(*it)->isHotelExist()
          && (*it)->getHouseNum() == lowestNumberInOneSet((*it)->getSetID()))
        propertyUpgradeable.push_back(*it);
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

void Player::resetOwner() {
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it) {
    (*it)->setOwner(this);
  }
  //ownedProperty.clear();
}

bool Player::RollDice(vector<ptrToPlace>::iterator begin, vector<ptrToPlace>::iterator end) {
  int randomNum = Dice->RollDice();
  cout << this->getPlayerName() << ", you rolled a " << randomNum << "\n";
  if(!this->isInJail())
    this->moveForward(randomNum, begin, end);
  else {
    if(Dice->canRollAgain(1)){
      cout << "You got out of jail by rolling doubles" << endl;
      this->setJail(nullptr);
      //if a player get out of jail by rolling doubles, he cannot roll again no matter what
      Dice->resetCount();
      return false;
    } else {
      cout << "You are still stuck in jail" << endl;
    }
  }

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

void Player::endTurn() {
  rules->endTurn();
  if(numOfTurnLeftInJail > 0)
    --numOfTurnLeftInJail;
}

int Player::netWorthOfProperty() const {
  int netWorth = static_cast<int>(this->asset);
  for(auto it = ownedProperty.begin(), end = ownedProperty.end(); it != end; ++it){
    netWorth += (*it)->netWorthOfUpgrades();
  }
  return netWorth;
}

bool Player::operator<(const Player &butner) const {
  return this->netWorthOfProperty() < butner.netWorthOfProperty();
}

void Free_Parking::activate(Player& _player){
  if(rules->isMoneyInFP() && *money > 0){
    _player.assetChange(*money);
    cout << _player.getPlayerName() << " got $" << *money << " for landing on " << this->name << endl;
    *money = 0;
  }
}

void Pay_Bank::activate(Player &_player) {
  while(_player.getAsset() < paidMoney && _player.anyPropertyDowngradeable()) {
    _player.sellUpgradeToAvoidBankrupt(paidMoney);
  }

  double moneyReceive = _player.assetChange(-paidMoney);
  //decide whether the money go free parking
  if(rules->isMoneyInFP())
    *moneyInFreeParking += moneyReceive;

  //this indicates that Player has bankrupt
  if(!_player.isPlayerExist()) {
    _player.resetOwner();
    cout << _player.getPlayerName() << " went bankrupt by landing on " << this->name << endl;
  } else {
    cout << _player.getPlayerName() << " paid the bank $" << (int)moneyReceive
         << " for landing on " << this->name << endl;
  }
}

void GoToJail::activate(Player &_player) {
  auto jailAssociated = dynamic_cast<Jail*>((*jailPlace).get());
  cout << _player.getPlayerName() << ", you were sent to " << jailAssociated->getName()
       << " for " << jailAssociated->getMaxNumOfTurns() << " turns" << endl;
  _player.setPlayerPlace(jailPlace);
  _player.setJail(jailAssociated);
}

void Jail::activate(Player &butner) {
  //if player is not in jail, nothing happens
  if(!butner.isInJail())
    return;

  if(butner.getNumOfTurnLeftInJail() == 0) {
    while(butner.getAsset() < moneyNeedToPay && butner.anyPropertyDowngradeable()) {
      butner.sellUpgradeToAvoidBankrupt(moneyNeedToPay);
    }

    double moneyReceive = butner.assetChange(-moneyNeedToPay);
    //decide whether the money go free parking
    if(rules->isMoneyInFP())
      *moneyInFreeParking += moneyReceive;

    //this indicates that Player has bankrupt
    if(!butner.isPlayerExist()) {
      butner.resetOwner();
      cout << butner.getPlayerName() << " went bankrupt when paying to leave jail" << endl;
    } else{
      //if player still exists after paying money, they should be freed from jail
      cout << butner.getPlayerName() << ", you had to pay $" << this->moneyNeedToPay
           << " to get out of jail" << endl;
      butner.setJail(nullptr);
    }
    return;
  }
  cout << butner.getPlayerName() << " you are in jail for "
       << butner.getNumOfTurnLeftInJail() << " turns." << endl;
  if(static_cast<int>(butner.getAsset()) >= butner.getJailPayment() && butner.getNumOfTurnLeftInJail() > 0) {
    cout << "Would you like to pay $" << butner.getJailPayment()
         << " to leave jail early?" << endl;
    cout << "y for yes and n for no: ";
    char playerChoice;
    cin >> playerChoice;
    if (playerChoice == 'y') {
      butner.assetChange(-(butner.getJailPayment()));
      butner.setJail(nullptr);
    }
    return;
  }
}