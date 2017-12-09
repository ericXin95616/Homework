#include "RandW.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct point{
	int x;
	int y;
} Point;
Point max(const Point a, const Point b);
Point min(const Point a, const Point b);

Point min(const Point a, const Point b) {
	if( a.x < b.x)
		return a;
	else if(a.x == b.x){
		if(a.y < b.y)
			return a;
	}
	return b;
}

Point max(const Point a, const Point b) {
	if( a.x > b.x )
		return a;
	else if(a.x == b.x) {
		if(a.y > b.y)
			return a;
	}
	return b;
}

//this function still need to be improved!!!
bool w_input(Point *a, Point *b, const int row, const int col, const char *s);
bool w_input(Point *a, Point *b, const int row, const int col, const char *s) {
	char ch;
	if( sscanf(s, " %c %d %d %d %d", &ch, &(a->x), &(a->y), &(b->x), &(b->y) ) == 5 ) {
		if(a->x >= 0 && a->x <= row - 1 && a->y >= 0 && a->y <= col - 1
			&& b->x >= 0 && b->x <= row - 1 && b->y >= 0 && b->y <= col - 1)
			return true;
	}
	return false;
}

bool is_horizon(const Point a, const Point b);
bool is_vertical(const Point a, const Point b);
bool is_right_diagnose(const Point a, const Point b);
bool is_left_diagnose(const Point a, const Point b);
char is_straight_line(const Point a, const Point b);
//a.y < b.y
void draw_Horizon(char** broad, const Point a, const Point b, const char ch);
//a.x < b.x
void draw_Vertical(char** broad, const Point a, const Point b, const char ch);
//a.x > b.x  a.y < b.y
void draw_right_diagnose(char** broad, const Point a, const Point b, const char ch);
//a.x < b.x  a.y < b.y
void draw_left_diagnose(char** broad, const Point a, const Point b, const char ch);

void draw(char** broad, const int x, const int y, const char ch);

void write(char** broad, const int row, const int col, const char *s) {
	Point ap, bp;
	ap.x = 0;
	ap.y = 0;
	bp.x = 0;
	bp.y = 0;
	
	if( !w_input(&ap, &bp, row, col, s) ) {
		printf("Improper draw command.\n");
		return;
	}
	
	char ch = is_straight_line(ap, bp);
	
	switch(ch) {
		case '-': draw_Horizon(broad, min(ap, bp), max(ap, bp), ch); break;
		case '|': draw_Vertical(broad, min(ap, bp), max(ap, bp), ch); break;
		case '\\': draw_right_diagnose(broad, max(ap, bp), min(ap, bp), ch); break;
		case '/': draw_left_diagnose(broad, min(ap, bp), max(ap, bp), ch); break;
		default: printf("Cannot draw the line as it is not straight.\n");
	}
}

bool e_input(Point *a, const int row, const int col, const char *s);
bool e_input(Point *a, const int row, const int col, const char *s) {
	char ch;
	if( sscanf(s, " %c %d %d", &ch, &(a->x), &(a->y)) == 3 ) {
		if(a->x >= 0 && a->x <= row - 1 && a->y >= 0 && a->y <= col - 1)
			return true;
	}
	return false;
}

void erase(char** broad, const int row, const int col, const char *s) {
	Point a;
	a.x = 0;
	a.y = 0;
	
	if(!e_input(&a, row, col, s)) {
		printf("Improper erase command.\n");
		return;
	}
	
	broad[a.x][a.y] = '*';
}

bool is_horizon(const Point a, const Point b) {
	return a.x == b.x;
}
bool is_vertical(const Point a, const Point b) {
	return a.y == b.y;
}
bool is_right_diagnose(const Point a, const Point b) {
	return (a.x - b.x) == -(a.y - b.y);
}
bool is_left_diagnose(const Point a, const Point b) {
	return (a.x - b.x) == (a.y - b.y);
}
char is_straight_line(const Point a, const Point b) {
	if(is_horizon(a, b))
		return '-';
	if(is_vertical(a, b))
		return '|';
	if(is_right_diagnose(a, b))
		return '\\';
	if(is_left_diagnose(a, b))
		return '/';
	return '*';
}

//a.y < b.y
void draw_Horizon(char** broad, const Point a, const Point b, const char ch) {
	int row = a.x;
	for(int i = a.y; i <= b.y; ++i) {
		draw(broad, row, i, ch);
	}
}
//a.x < b.x
void draw_Vertical(char** broad, const Point a, const Point b, const char ch) {
	int col = a.y;
	for(int i = a.x; i <= b.x; ++i) {
		draw(broad, i, col, ch);
	}
}
//a.x > b.x  a.y < b.y
void draw_right_diagnose(char** broad, const Point a, const Point b, const char ch) {
	for(int i = a.x, j = a.y; i >= b.x; --i) {
		draw(broad, i, j, ch);
		++j;
	}
}
//a.x < b.x  a.y < b.y
void draw_left_diagnose(char** broad, const Point a, const Point b, const char ch) {
	for(int i = a.x, j = a.y; i <= b.x; ++i) {
		draw(broad, i, j, ch);
		++j;
	}
}

void draw(char** broad, const int x, const int y, const char ch) {
	if(broad[x][y] == '*') {
		broad[x][y] = ch;
		return;
	}
	
	if(broad[x][y] != ch) {
		broad[x][y] = '+';
	}
}








