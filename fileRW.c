#include "fileRW.h"
#include "Broad.h"
#include <stdio.h>
#include <stdbool.h>
#define MAX_LENGTH 1000

bool sl_input(char *str, const char *s);
bool sl_input(char *str, const char *s) {
	char ch;
	if( sscanf(s, " %c %s", &ch, str) == 2) {
		int a = 0;
		while(str[a] != '\0') {
			++a;
		}
		//printf("a = %d\n", a);
		if( a <= 4)
			return false;
		if(str[a - 1] == 't' && str[a - 2] == 'x' 
			&& str[a - 3] == 't' && str[a - 4] == '.')
				return true;
	}
	return false;
}

void save(char** broad, const int row, const int col, const char *s) {
	char str[MAX_LENGTH];
	if( !sl_input(str, s)) {
		printf("Improper save command or file could not be created.\n");
		return;
	}
	FILE *fp = fopen(str, "w");
	if(!fp) {
		printf("Improper save command or file could not be created.\n");
		return;
	}
	
	fprintf(fp, "%d %d\n", row, col);
	for(int i = 0; i < row; ++i) {
		for(int j = 0; j < col; ++j) {
			fprintf(fp, "%c", broad[i][j]);
		}
	}
	fclose(fp);
}

void load(char*** ptBroad, int *row, int *col, const char *s) {
	char str[MAX_LENGTH];
	if( !sl_input(str, s)) {
		printf("Failed to open file: %s\n", str);
		return;
	}
	FILE *fp = fopen(str, "r");
	if( !fp ) {
		printf("Improper load command or file could not be opened.\n");
		return;
	}
	
	freebroad(ptBroad, *row);
	fscanf(fp, "%d %d", row, col);
	*(ptBroad) = broadCreation(*row, *col);
	//fscanf(fp, "%c", &(*ptBroad)[0][0]);
	for(int i = 0; i < *row; ++i) {
		for(int j = 0; j < *col; ++j) {
			fscanf(fp, " %c", &(*ptBroad)[i][j]);
		}
	}
}



