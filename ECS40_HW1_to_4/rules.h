#ifndef RULES_H
#define RULES_H

namespace Monopoly{
	class Rules{
		public:
			Rules(int _thresholdHouseNum, int _setMultiply, int _salaryMutiply, int _turnLimit, int _endNumOfPlayer,
				bool build, bool money, bool auction, int _maxDoubleLimit);
			int getThresholdHouseNum()const {return thresholdHouseNum;}
			int getSetMultiply()const {return setMultiply;}
			int getSalaryMultiply()const {return salaryMultiply;}
			int getEndOfPlayer()const {return endNumOfPlayer;}
			int getMaxDoubleLimit()const {return maxDoubleLimit;}
			bool isBuildEvenly()const {return buildEvenly;}
			bool isMoneyInFP()const {return moneyInFreeParking;}
			bool isAuctionAllow()const {return isAuction; }
			bool isReachTurnLimit()const {return (turnLimit != -1)&&(countTurn >= turnLimit);}
			void endTurn() {++countTurn;}

		private:
			int thresholdHouseNum; //Number of house being built before upgrading to hotel
			int setMultiply;
			int salaryMultiply;
			static int countTurn;//indicate which turn it is (initialize as 0)
			int turnLimit;//the largest possible number of turn
			int endNumOfPlayer;
			bool buildEvenly;
			bool moneyInFreeParking;
			bool isAuction;
			int maxDoubleLimit;
	};
}

#endif
