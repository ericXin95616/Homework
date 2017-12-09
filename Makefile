paint.out : paint.o Broad.o Command.o RandW.o fileRW.o
	gcc paint.o Broad.o Command.o RandW.o fileRW.o -o paint.out

paint.o : paint.c Broad.c Broad.h Command.c Command.h fileRW.c fileRW.h RandW.c RandW.h
	gcc -Wall -c paint.c

Command.o : Command.c Command.h
	gcc -Wall -c Command.c

RandW.o : RandW.c RandW.h 
	gcc -Wall -c RandW.c

Broad.o : Broad.c Broad.h
	gcc -Wall -c Broad.c
	
fileRW.o : fileRW.c fileRW.h Broad.c Broad.h
	gcc -Wall -c fileRW.c

clean :
	rm *.o paint.o
