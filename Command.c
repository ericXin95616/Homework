#include "Command.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
//this function will be changed later
//I will print warning message after revision
bool verifyInteger(const char *str) {
	int temp = 0;
	char tempStr[20];	
	if( sscanf(str, "%d%s", &temp, tempStr) == 1 ) {
		if(sscanf(str, "%d", &temp))
			return true;
	}
	return false;
}

void commandInput(const int argc, const char *argv[], int *row, int *col) {
	*row = 10;
	*col = 10;
	
	if(argc == 1 || argc == 3) {
		if(argc == 1)
			return;
		
		if(argc == 3) {
			if( verifyInteger(argv[1]) ) {
				if( verifyInteger(argv[2]) ){
					if( atoi(argv[1]) >= 1 ) {
						if( atoi(argv[2]) >= 1 ) {
							*row = atoi(argv[1]);
							*col = atoi(argv[2]);
						} else {
							printf("The number of columns is less than 1.\n");
							printf("Making default board of 10 X 10.\n");
							return;
						}
					} else {
						printf("The number of rows is less than 1.\n");
						printf("Making default board of 10 X 10.\n");
						return;
					}
				} else {
					printf("The number of columns is not an integer.\n");
					printf("Making default board of 10 X 10.\n");
					return;
				}
			} else {
				printf("The number of rows is not an integer.\n");
				printf("Making default board of 10 X 10.\n");
				return;
			}
		}
	} else {
		printf("Wrong number of command line arguements entered.\n");
		printf("Usage: ./paint.out [num_rows num_cols]\n");
		printf("Making default board of 10 X 10.\n");
	}
}

void printHelp() {
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

bool qh_check(const char *str);
bool w_check(const char *str);
bool re_check(const char *str);
bool ad_check(const char *str);
bool sl_check(const char *str);

bool format_check(const char *str) {
	char ch;
	if( sscanf(str, " %c", &ch) == 1) {
		if( ch == 'q' || ch == 'h' || ch == 'w' 
			|| ch == 'r' || ch == 'e' || ch == 'a'
			|| ch == 'd' || ch == 's' || ch == 'l') {
				char temp;
				sscanf(str, " %c%c", &ch, &temp);
				if(isspace(temp)) {
					switch(ch) {
						case 'q': case 'h': return qh_check(str);
						default: return true;
 					}
				}	
			}
	}
	return false;
}

bool qh_check(const char *str) {
	char ch;
	char _ch;
	if( sscanf(str, " %c %c", &ch, &_ch) == 2) {
		//printf("_ch == %c\n", _ch);
		if(_ch != '\n')
			return false;
	}
	return true;
}
/*
bool w_check(const char *str) {
	char ch;
	int a, b, c, d;
	return ( sscanf(str, " %c %d %d %d %d", &ch, &a, &b, &c, &d) == 5 );
}

bool re_check(const char *str) {
	char ch;
	int a, b;
	return ( sscanf(str, " %c %d %d", &ch, &a, &b) == 3 );
}

bool ad_check(const char *str) {
	char ch, _ch;
	int a;
	return ( sscanf(str, " %c %c %d", &ch, &_ch, &a) == 3 );
}

bool sl_check(const char *str) {
	char ch;
	char _str[100];
	return ( sscanf(str, " %c %s", &ch, _str) == 2);
}
*/










