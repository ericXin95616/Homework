#include "Broad.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char** broadCreation(const int row, const int col) {
	char **broad = (char**)malloc(row * sizeof(char*));
	for(int i = 0; i < row; ++i) {
		broad[i] = (char*)malloc(col * sizeof(char));
	}
	for(int i = 0; i < row; ++i) {
		for(int j = 0; j < col; ++j) {
			broad[i][j] = '*';
		}
	}
	return broad;
}

void broadOutput(const char *broad[], const int row, const int col) {
	for(int i = 0; i < row; ++i) {
		printf("%d ", row - (i + 1));
		for(int j = 0; j < col; ++j) {
			printf("%c ", broad[row - i - 1][j]);
		}
		printf("\n");
	}
	printf("  ");
	for(int i = 0; i < col; ++i)
		printf("%d ", i);
	printf("\n");
}

void freebroad(char*** ptBroad, const int row) {
	for(int i = 0; i < row; ++i) {
		free( (*ptBroad)[i] );
	}
	free(*ptBroad);
	*ptBroad = NULL;
}

bool ad_input(char *RC, int *num, const int row, const int col, const char *s);
void addRow(char** broad, const int row_num, const int row, const int col);
void addCol(char** broad, const int col_num, const int row, const int col);
char* row_copy(char* des, char* src, const int size);
void deleteRow(char** broad, const int row_num, const int row, const int col);
void deleteCol(char** broad, const int col_num, const int row, const int col);

bool ad_input(char *RC, int *num, const int row, const int col, const char* s) {
	char ch;
	if( sscanf(s, " %c %c %d", &ch, RC, num) == 3 ) {
		if( (*RC == 'r' || *RC == 'c') ) {
			if(*RC == 'r') {
				return (*num >= 0) && (*num <= row);
			} else {
				return (*num >= 0) && (*num <= col);
			}
		}
	}
	return false;
}


void addRow(char** broad, const int row_num, const int row, const int col) {
	char** temp = (char**)realloc(broad, row * sizeof(char*));
	if(!temp) {
		printf("Row-realloc fails!\n");
		return;
	}
	broad[row - 1] = (char*)malloc(col * sizeof(char));
	for(int i = row - 1; i > row_num; --i) {
		row_copy(broad[i], broad[i - 1], col);
	}
	for(int i = 0; i < col; ++i) {
		broad[row_num][i] = '*';
	}
}

void addCol(char** broad, const int col_num, const int row, const int col) {
	for(int i = 0; i < row; ++i) {
		char* temp = realloc(broad[i], col * sizeof(char));
		
		if(!temp) {
			printf("Col-realloc fails!\n");
			return;
		}
		
		for(int j = col - 1; j > col_num; --j) {
			broad[i][j] = broad[i][j - 1];
		}
		broad[i][col_num] = '*';
	}
}

char* row_copy(char* des, char* src, const int size) {
	for(int i = 0; i < size; ++i) {
		des[i] = src[i];
	}
	return des;
}

void deleteRow(char** broad, const int row_num, const int row, const int col) {
	for(int i = row_num; i < row; ++i) {
		row_copy(broad[i], broad[i + 1], col);
	}
	free(broad[row]);
	char** temp = (char**)realloc(broad, row * sizeof(char*));
	
	if( !temp ) {
		printf("Delete row fails!\n");
		return;
	}
}

void deleteCol(char** broad, const int col_num, const int row, const int col) {
	for(int i = 0; i < row; ++i) {
		for(int j = col_num; j < col; ++j) {
			broad[i][j] = broad[i][j + 1];
		}
		char* temp = (char*)realloc(broad[i], col * sizeof(char));
		if(!temp) {
			printf("Delete col fails!\n");
			return;
		}
	}
}

void addRowCol(char** broad, int *row, int *col, const char *s) {
	char RC;
	int num = 0;
	
	if( !ad_input(&RC, &num, *row, *col, s) ) {
		printf("Improper add command.\n");
		return;
	}
	
	if( RC == 'r' ) {
		addRow(broad, num, ++(*row), *col);
	} else {
		addCol(broad, num, *row, ++(*col));
	}
}

void deleteRowCol(char** broad, int *row, int *col, const char *s) {
	char RC;
	int num = 0;
	
	if( !ad_input(&RC, &num, *row - 1, *col - 1, s) ) {
		printf("Improper delete command.\n");
		return;
	}
	
	if( RC == 'r' ) {
		deleteRow(broad, num, --(*row), *col);
	} else {
		deleteCol(broad, num, *row, --(*col));
	}
}

bool r_input(int *row, int *col, const char *s);
//void fillBroad(char** broad, const int row, const int col);

bool r_input(int *row, int *col, const char *s) {
	char ch;
	if(sscanf(s, " %c %d %d", &ch, row, col) == 3) {
		return (*row >= 1) && (*col >= 1);
	}
	return false;
}

int _min(const int a, const int b);
int _min(const int a, const int b) { return (a < b) ? a : b;}
void resize(char*** ptBroad, int *row, int *col, const char *s) {
	int initialRow = *row;
	int initialCol = *col;
	if( !r_input(row, col, s) ) {
		*row = initialRow;
		*col = initialCol;
		printf("Improper resize command.\n");
		return;
	}
	char** newBroad = broadCreation(*row, *col);

	for(int i = 0; i < _min(initialRow, *row); ++i) {
		for(int j = 0; j < _min(initialCol, *col); ++j)
			newBroad[i][j] = (*ptBroad)[i][j];
	}
	freebroad(ptBroad, initialRow);
	(*ptBroad) = newBroad;
}













