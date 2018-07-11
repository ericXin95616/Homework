hoarding.out : main.o rules.o OtherClass.o Property.o setGame.o Game.o
	g++ -g -std=c++14 -Wall -Werror -o hoarding.out main.o rules.o OtherClass.o Property.o setGame.o Game.o
main.o : main.cpp rules.cpp rules.h OtherClass.cpp OtherClass.h Property.cpp Property.h setGame.cpp setGame.h Game.cpp Game.h
	g++ -g -std=c++14 -Wall -Werror -c main.cpp
rules.o: rules.cpp rules.h
	g++ -g -std=c++14 -Wall -Werror -c rules.cpp
OtherClass.o: OtherClass.cpp OtherClass.h rules.cpp rules.h Property.cpp Property.h
	g++ -g -std=c++14 -Wall -Werror -c OtherClass.cpp
Property.o : Property.cpp Property.h rules.cpp rules.h OtherClass.cpp OtherClass.h
	g++ -g -std=c++14 -Wall -Werror -c Property.cpp
setGame.o : setGame.cpp setGame.h Property.cpp Property.h rules.cpp rules.h OtherClass.cpp OtherClass.h
	g++ -g -std=c++14 -Wall -Werror -c setGame.cpp
Game.o : Game.cpp Game.h Property.cpp Property.h rules.cpp rules.h OtherClass.cpp OtherClass.h
	g++ -g -std=c++14 -Wall -Werror -c Game.cpp
clean :
	rm *.o hoarding.out


