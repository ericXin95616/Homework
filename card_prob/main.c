#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LENGTH 1000

bool intInput(int *integer);
double card_prob(int totalCard, int copiesCard, int initialHand, int mulliganCard, int turnNum);
double combine(int n, int m);
double fact(int m);

bool intInput(int *integer) {
  if (!scanf(" %d", integer)) {
    return false;
  } else {
    if(*integer < 0)
      return false;

    char temp;
    scanf("%c", &temp);

    if(temp == '\n') {
      return true;
    }

    while(temp == ' ') {
      scanf("%c", &temp);
    }
    if (temp == '\n')
      return true;
    return false;
  }
}

double card_prob(int totalCard, int copiesCard, int initialHand, int mulliganCard, int turnNum) {
  return 1.0 - combine(initialHand, totalCard - copiesCard) *
      combine(mulliganCard, totalCard - copiesCard - initialHand) * combine(turnNum, totalCard - copiesCard - initialHand) /
      (combine(initialHand, totalCard) * combine(mulliganCard, totalCard - initialHand) * combine(turnNum, totalCard - initialHand));
}

double combine(int n, int m) {
  if(n == 0)
    return 1.0;
  double comNum = 1.0;
  double M = m;
  double numerator = n;
  comNum *= m / numerator;
  while(1) {
    if(numerator != 1)
      numerator--;
    if( m > M - n + 1)
      m--;
    else m = 1;
    comNum *= m / numerator;
    if(numerator == 1 && m == 1)
      break;
  }
  return comNum;
}

double fact(int m) {
  double factNum = 1.0;
  for(int i = 1; i <= m; i++) {
    factNum *= (double)i;
  }
  return factNum;
}

int main() {
  int totalCard = 0;
  char buf[MAX_LENGTH];
  printf("Enter how many total cards there are in the deck: ");
  while( !intInput(&totalCard) ) {
    fgets(buf, MAX_LENGTH, stdin);
    printf("Enter how many total cards there are in the deck: ");
  }

  int copiesCard = 0;
  printf("Enter how many copies of the card that you are looking for are in the deck: ");
  while( !intInput(&copiesCard) ) {
    fgets(buf, MAX_LENGTH, stdin);
    printf("Enter how many copies of the card that you are looking for are in the deck: ");
  }

  int initialHand = 0;
  printf("Enter your initial hand size: ");
  while( !intInput(&initialHand) ) {
    fgets(buf, MAX_LENGTH, stdin);
    printf("Enter your initial hand size: ");
  }

  int mulliganCard = 0;
  printf("Enter how many cards you are mulliganing: ");
  while( !intInput(&mulliganCard) ) {
    fgets(buf, MAX_LENGTH, stdin);
    printf("Enter how many cards you are mulliganing: ");
  }

  int turnNum = 0;
  printf("Enter what turn you want to draw the card by: ");
  while( !intInput(&turnNum) ) {
    fgets(buf, MAX_LENGTH, stdin);
    printf("Enter what turn you want to draw the card by: ");
  }

  printf("The probability of drawing at least one of the cards by turn %d given you mulliganed %d cards is %.2lf\n",
         turnNum, mulliganCard, card_prob(totalCard, copiesCard, initialHand, mulliganCard, turnNum));
}