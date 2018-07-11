#ifndef OTHERCLASS_H
#define OTHERCLASS_H

#include "Property.h"
#include "rules.h"
#include <stdio.h>
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;

namespace Monopoly{
 class Space;
 class Player;
 typedef unique_ptr<Space> ptrToPlace;
 typedef shared_ptr<Rules> ptrToRules;

class DiceRoller{
 public:
  DiceRoller();
  DiceRoller(FILE *_fp):fpRandom(_fp){}
  ~DiceRoller();
  void setPtrs(FILE *_fp);
  int  RollDice();
  bool canRollAgain(int maxDoubleLimit);
  void resetCount() {count = 0;}
 private:
  FILE *fpRandom;
  int randomNumber1;
  int randomNumber2;
  int count;
};

class Board{
 public:
  Board() = default;
  void push_back(ptrToPlace &&);
  const ptrToPlace& at(size_t i)const ;
  vector<ptrToPlace>::iterator begin();
  vector<ptrToPlace>::const_iterator cbegin()const ;
  vector<ptrToPlace>::iterator end();
  vector<ptrToPlace>::const_iterator cend()const ;
  size_t size()const {return board.size();}
  void setPtrToPlayerGroup(vector<Player> *playerGroup);
 private:
  vector<ptrToPlace> board;
};

class Gamestate{
 public:
  Gamestate() = default;
  Gamestate(const ptrToRules &_rules):rules(_rules){}
  void setPtrToRules(const ptrToRules &_rules){ rules = _rules; }
  bool isReachTurnLimit() const{return rules->isReachTurnLimit();}
 private:
  ptrToRules rules;
};
}
#endif
