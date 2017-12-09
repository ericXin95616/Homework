#ifndef COMMAND_H
#define COMMAND_H
#include <stdbool.h>

void commandInput(const int argc, const char *argv[], int *row, int *col);
void printHelp();
bool format_check(const char *str);

#endif
