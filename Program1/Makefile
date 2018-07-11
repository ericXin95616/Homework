all: consistentresultverification sortedverification timealgorithms

consistentresultverification: consistentresultverification.cxx json.hpp
	g++ -g -std=c++14 -Wall -Werror -o consistentresultverification consistentresultverification.cxx json.hpp

sortedverification: sortedverification.cxx json.hpp
	g++ -g -std=c++14 -Wall -Werror -o sortedverification sortedverification.cxx json.hpp
	
timealgorithms: timealgorithms.cxx json.hpp insertionsort.cpp insertionsort.h quicksort.cpp quicksort.h mergesort.cpp mergesort.h 
	g++ -g -std=c++14 -Wall -Werror -o timealgorithms timealgorithms.cxx json.hpp insertionsort.cpp insertionsort.h quicksort.cpp quicksort.h mergesort.cpp mergesort.h 
