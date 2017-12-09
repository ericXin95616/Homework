#include <stdio.h>
#include <stdlib.h>
#include "Command.h"
#include "RandW.h"
#include "Broad.h"
#include "fileRW.h"
#define _MAX_LENGTH 1000

int main(const int argc, const char *argv[]) {
	int row = 0, col = 0;
	commandInput(argc, argv, &row, &col);
	
	char **broad = broadCreation(row, col);
	//broadOutput((const char**)broad, row, col);
	
	char instruction;
	char commandLine[_MAX_LENGTH];
	//printf("Enter your command: ");
	do {
		broadOutput((const char**)broad, row, col);
		printf("Enter your command: ");
		
		fgets(commandLine, _MAX_LENGTH, stdin);
		if(format_check(commandLine)) {
			sscanf(commandLine, " %c", &instruction);
		} else {
			printf("Unrecognized command. Type h for help.\n");
			continue;
		}
		
		switch(instruction) {
			case 'q': freebroad(&broad, row); return 0;
			case 'h': printHelp(); break;
			case 'w': write(broad, row, col, commandLine); break;
			case 'e': erase(broad, row, col, commandLine); break;
			case 'r': resize(&broad, &row, &col, commandLine); break;
			case 'a': addRowCol(broad, &row, &col, commandLine); break;
			case 'd': deleteRowCol(broad, &row, &col, commandLine); break;
			case 's': save(broad, row, col, commandLine); break;
			case 'l': load(&broad, &row, &col, commandLine); break;
			default: printf("Unrecognized command. Type h for help.\n");
		}
		//broadOutput((const char**)broad, row, col);
		//printf("Enter your command: ");
	} while(true);
}



