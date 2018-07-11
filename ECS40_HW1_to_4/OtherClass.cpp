#include "OtherClass.h"
using namespace Monopoly;
// DiceRoller class
DiceRoller::DiceRoller() {
  randomNumber1 = 0;
  randomNumber2 = 0;
  count = 0;
  fpRandom = nullptr;
}

void DiceRoller::setPtrs(FILE *_fp) {
  fpRandom = _fp;
}

int DiceRoller::RollDice() {
  ++count;
  fscanf(fpRandom, " %d %d", &randomNumber1, &randomNumber2);
  randomNumber1 = randomNumber1 % 6 + 1;
  randomNumber2 = randomNumber2 % 6 + 1;
  return randomNumber1 + randomNumber2;
}

DiceRoller::~DiceRoller() {
  fclose(fpRandom);
  fpRandom = nullptr;
}


bool DiceRoller::canRollAgain(int maxDoubleLimit) {
  return (randomNumber1 == randomNumber2) && (count - 1 < maxDoubleLimit);
}

// Board class
void Board::push_back(ptrToPlace &&_place) {
  board.push_back(std::move(_place));
}

const ptrToPlace& Board::at(size_t i) const {
  if(i < 0 || i > board.size() - 1)
    throw std::out_of_range("The index you enter is out of range!\n");
  return board.at(i);
}

vector<ptrToPlace>::iterator Board::begin() {
  return board.begin();
}

vector<ptrToPlace>::iterator Board::end() {
  return board.end();
}

vector<ptrToPlace>::const_iterator Board::cbegin() const {
  return board.cbegin();
}
vector<ptrToPlace>::const_iterator Board::cend()const {
  return board.cend();
}

void Board::setPtrToPlayerGroup(vector<Player> *playerGroup){
  for(auto it = board.begin(); it != board.end(); ++it) {
    (*it)->setPlayerGroupPtr(playerGroup);
  }
}
