#ifndef BROAD_H
#define BROAD_H

#include <stdio.h>
#include <stdbool.h>

char** broadCreation(const int row, const int col);
void broadOutput(const char *broad[], const int row, const int col);
void freebroad(char*** ptBroad, const int row);

void addRowCol(char** broad, int *row, int *col, const char *s);
void deleteRowCol(char** broad, int *row, int *col, const char *s);
void resize(char*** ptBroad, int *row, int *col, const char *s);

#endif
