#include "rules.h"

using namespace Monopoly;

// Rule class
Rules::Rules(int _thresholdHouseNum, int _setMultiply, int _salaryMutiply, int _turnLimit, int _endNumOfPlayer,
      bool build, bool money, bool auction, int _maxDoubleLimt) : thresholdHouseNum(_thresholdHouseNum),
                                              setMultiply(_setMultiply),
                                              salaryMultiply(_salaryMutiply),
                                              turnLimit(_turnLimit),
                                              endNumOfPlayer(_endNumOfPlayer),
                                              buildEvenly(build),
                                              moneyInFreeParking(money),
                                              isAuction(auction), maxDoubleLimit(_maxDoubleLimt){}
int Rules::countTurn = 0;
