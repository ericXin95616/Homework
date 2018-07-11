#include "Property.h"
//#include "Go.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <cctype>
#include <memory>
#include <algorithm>

#define MAX_LENGTH 1000

using std::vector;
using std::cout;
using std::endl;
using std::cin;

namespace  Monopoly {
void getName(char *name, FILE *fp);
void ReadRules(FILE *rules, double &initialAsset, int &turnLimit, int &endNumOfPlayer, int &setMultiply,
               int &thresholdHouseNum, int &goSalaryMultiply, bool &evenBuildHouse, bool &moneyFreeParking,
               bool &isAuctionAollow, int &maxDoubleLimit);
char *toUpper(char *cstr);
bool strToBool(const char *cstr);

void getName(char *name, FILE *fp) {
  int j = 0;
  do {
    fscanf(fp, "%c", &(name[j]));
    ++j;
  } while (name[j - 1] != ',');
  name[j - 1] = '\0';
  //return name;
}

void ReadRules(FILE *rules, double &initialAsset, int &turnLimit, unsigned int &endNumOfPlayer, int &setMultiply,
               int &thresholdHouseNum, int &goSalaryMultiply, bool &evenBuildHouse, bool &moneyFreeParking,
               bool &isAuctionAollow, int &maxDoubleLimit) {
  char _evenBuildHouse[MAX_LENGTH];
  char _moneyFreeParking[MAX_LENGTH];
  char _isAuctionAollow[MAX_LENGTH];

  fscanf(rules,
         "Starting Cash: %lf\nTurn Limit (-1 for no turn limit): %d\nNumber of Players Left To End Game: %d\nProperty Set Multiplier: %d\n",
         &initialAsset,
         &turnLimit,
         &endNumOfPlayer,
         &setMultiply);

  fscanf(rules,
         "Number of Houses Before Hotels: %d\nMust Build Houses Evenly: %s\nPut Money In Free Parking: %s\nAuction Properties: %s\nSalary Multiplier For Landing On Go: %d\n",
         &thresholdHouseNum,
         _evenBuildHouse,
         _moneyFreeParking,
         _isAuctionAollow,
         &goSalaryMultiply);

  fscanf(rules, "Max Doubles ReRolls: %d", &maxDoubleLimit);

  evenBuildHouse = strToBool(toUpper(_evenBuildHouse));
  moneyFreeParking = strToBool(toUpper(_moneyFreeParking));
  isAuctionAollow = strToBool(toUpper(_isAuctionAollow));
}

char *toUpper(char *cstr) {
  for (unsigned int i = 0; i < strlen(cstr); ++i) {
    cstr[i] = toupper(cstr[i]);
  }
  return cstr;
}

bool strToBool(const char *cstr) {
  return !strcmp(cstr, "YES");
}

FILE *fileOpen(char *cstr) {
  FILE *fp = fopen(cstr, "r");
  if (fp == NULL) {
    printf("Fail to open the file whose name is %s\n", cstr);
    exit(0);
  }
  return fp;
}

vector<size_t > getMaxLens(const vector<Player> &playerGroup, const Board &map){
  vector<size_t > maxLens;
  size_t maxLenOfPlayerName = 0, maxLenOfPlaceName = 0;
  size_t maxLenOfUpgrades = (playerGroup.at(0).getThresholdHouseNum() > 8) ? playerGroup.at(0).getThresholdHouseNum() : 8;

  auto itOfMaxPlayer = std::max_element(playerGroup.begin(), playerGroup.end(),
                                        [](const Player &p1, const Player &p2) {
                                          return (p1.getPlayerName()).length() < (p2.getPlayerName()).length();
                                        });
  //5 is the length of the word "owner"
  maxLenOfPlayerName = (itOfMaxPlayer->getPlayerName().length() > 5) ?
                       itOfMaxPlayer->getPlayerName().length() : 5;

  auto itOfMaxPlace = std::max_element(map.cbegin(), map.cend(),
                                       [](auto &p1, auto &p2) {
                                         return p1->getName().length() < p2->getName().length();
                                       });
  //10 is the length of the word "Space name"
  maxLenOfPlaceName = ((*itOfMaxPlace)->getName().length() > 10) ?
                      (*itOfMaxPlace)->getName().length() : 10;

  maxLens.push_back(maxLenOfPlaceName);
  maxLens.push_back(maxLenOfPlayerName);
  maxLens.push_back(maxLenOfUpgrades);
  return maxLens;
}



//here is the function we need
void gameSet(char **argv, int numOfPlayer, Board &map, vector<Player> &playerGroup, Gamestate &gamestate) {

  FILE *fpRules = fileOpen(argv[1]);
  FILE *fpBoard = fileOpen(argv[2]);
  FILE *fpRandom = fileOpen(argv[3]);

  ptrToDice dice = std::make_shared<DiceRoller>(fpRandom);

  double initialAsset;
  unsigned int endNumOfPlayer;
  int turnLimit, setMultiply, thresholdHouseNum, goSalaryMultiply, maxDoubleLimit;
  bool evenBuildHouse, moneyFreeParking, isAuctionAollow;
  ReadRules(fpRules, initialAsset, turnLimit, endNumOfPlayer, setMultiply, thresholdHouseNum,
            goSalaryMultiply, evenBuildHouse, moneyFreeParking, isAuctionAollow, maxDoubleLimit);

  ptrToRules rules = std::make_shared<Rules>(thresholdHouseNum, setMultiply, goSalaryMultiply, turnLimit, endNumOfPlayer,
                                             evenBuildHouse, moneyFreeParking, isAuctionAollow, maxDoubleLimit);

  gamestate.setPtrToRules(rules);

  int propertyNum = 0;
  fscanf(fpBoard,
         "Number of Spaces,%d,,,,,,,,\n,,,,,,,,,\n,,,,,,,,,\nType,Set Id,Intraset Id,Name,Property Cost,House Cost,Hotel Cost,Rent,Rent with House,Rent With Hotel\n",
         &propertyNum);

  auto propertyPerSet = std::make_shared<vector<unsigned int> >(); // use this to record how many properties each set has
  int previousID = 0;
  unsigned int numProperty = 0;

  shared_ptr<int> moneyInFreeParking = std::make_shared<int>(0);
  for (int i = 0; i < propertyNum; ++i) {
    char Type[MAX_LENGTH];
    getName(Type, fpBoard);

    //printf("%s\n", Type);
    if (strcmp(Type, "Property") == 0) {
      char propertyName[MAX_LENGTH];
      int setID;
      int intrasetID;
      double cost;
      double houseCost;
      double hotelCost;
      double rent;
      double rentHouse;
      double rentHotel;
      fscanf(fpBoard, "%d,%d,", &setID, &intrasetID);
      //cout << setID << " " << intrasetID << endl;

      getName(propertyName, fpBoard);

      fscanf(fpBoard, "%lf,%lf,%lf,%lf,%lf,%lf\n", &cost, &houseCost, &hotelCost, &rent, &rentHouse, &rentHotel);
      ptrToPlace temp = std::make_unique<Property>(setID, intrasetID, propertyName, cost,
                                                          houseCost, hotelCost, rent, rentHouse, rentHotel, rules);
      map.push_back(std::move(temp));
      //understand the number of properties
      if (previousID == setID)
        ++numProperty;
      else {
        int size = propertyPerSet->size();
        if (setID < size) {
          ++(propertyPerSet->at(setID));
        } else {
          previousID = setID;
          propertyPerSet->push_back(numProperty);
          numProperty = 1;
        }
      }
    } else if(string(Type) == "Go"){

      int moneyCollect;
      fscanf(fpBoard, "%d,", &moneyCollect);
      char goName[MAX_LENGTH];
      getName(goName, fpBoard);
      fscanf(fpBoard, ",,,,,,\n");
      //haven't read salaryMultiply
      ptrToPlace temp = std::make_unique<Go>(moneyCollect, goName, rules);
      map.push_back(std::move(temp));

    } else if(string(Type) == "FreeParking"){

      char name[MAX_LENGTH];
      getName(name, fpBoard);
      fscanf(fpBoard, ",,,,,,,\n");
      ptrToPlace temp = std::make_unique<Free_Parking>(rules, name, moneyInFreeParking);
      map.push_back(std::move(temp));

    } else if(string(Type) == "GoToJail"){

      char name[MAX_LENGTH];
      getName(name, fpBoard);
      int indexOfJail;
      fscanf(fpBoard, "%d,,,,,,,\n", &indexOfJail);
      ptrToPlace temp = std::make_unique<GoToJail>(rules, name, indexOfJail);
      map.push_back(std::move(temp));

    } else if(string(Type) == "Jail"){

      char name[MAX_LENGTH];
      getName(name, fpBoard);
      int maxNumOfTurns, moneyNeedToPay;
      fscanf(fpBoard, "%d,%d,,,,,,\n", &maxNumOfTurns, &moneyNeedToPay);
      ptrToPlace temp = std::make_unique<Jail>(rules, name, maxNumOfTurns, moneyNeedToPay, moneyInFreeParking);
      map.push_back(std::move(temp));

    } else if(string(Type) == "Pay"){

      char name[MAX_LENGTH];
      getName(name, fpBoard);
      int moneyNeedToPay;
      fscanf(fpBoard, "%d,,,,,,,\n", &moneyNeedToPay);
      ptrToPlace temp = std::make_unique<Pay_Bank>(rules, name, moneyInFreeParking, moneyNeedToPay);
      map.push_back(std::move(temp));

    }
  }
  //push back the last number
  propertyPerSet->push_back(numProperty);

  //set GoToJail's iterator
  auto beginOfMap = map.begin();
  for(auto it = map.begin(); it != map.end(); ++it) {
    GoToJail* goJail = dynamic_cast<GoToJail* >((*it).get());
    if(goJail != nullptr)
      goJail->setJailIterator(beginOfMap);
  }

  //construct Player class
  string userName;
  cin.get(); // this means to eat the space after the first cin
  for (int l = 1; l <= numOfPlayer; ++l) {
    cout << "Enter the name of player " << l << ": ";
    getline(cin, userName);
    playerGroup.emplace_back(l, userName, initialAsset, map.begin(), propertyPerSet, rules, dice);
  }

  map.setPtrToPlayerGroup(&playerGroup);

  vector<size_t > maxLens = getMaxLens(playerGroup, map);
  int spaceNumber = 0;
  for(auto it = map.begin(), end = map.end(); it != end; ++it) {
    (*it)->setMaxLens(maxLens.at(0), maxLens.at(1), maxLens.at(2));
    (*it)->setSpaceNumber(spaceNumber++);
  }

  fclose(fpBoard);
  fclose(fpRules);
}
}

