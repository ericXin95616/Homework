Matrix.out : main.o Matrix.o RowItr.o RowElementItr.o ColItr.o ColElementItr.o MatrixError.o MatrixSizeError.o MatrixSizeMismatchError.o MatrixInnerDimensionMismatchError.o
	g++ -g -std=c++14 -Wall -Werror -o Matrix.out main.o Matrix.o RowItr.o RowElementItr.o ColItr.o ColElementItr.o MatrixError.o MatrixSizeError.o MatrixSizeMismatchError.o MatrixInnerDimensionMismatchError.o
main.o : main.cpp Matrix.h Matrix.cpp
	g++ -g -std=c++14 -Wall -Werror -c main.cpp
Matrix.o : Matrix.cpp Matrix.h RowItr.cpp RowItr.h RowElementItr.cpp RowElementItr.h ColItr.cpp ColItr.h ColElementItr.cpp ColElementItr.h MatrixError.cpp MatrixError.h MatrixSizeError.cpp MatrixSizeError.h MatrixSizeMismatchError.cpp MatrixSizeMismatchError.h MatrixInnerDimensionMismatchError.cpp MatrixInnerDimensionMismatchError.h
	g++ -g -std=c++14 -Wall -Werror -c Matrix.cpp
RowItr.o : RowItr.cpp RowItr.h Matrix.cpp Matrix.h RowElementItr.cpp RowElementItr.h
	g++ -g -std=c++14 -Wall -Werror -c RowItr.cpp
RowElementItr.o : RowElementItr.cpp RowElementItr.h RowItr.coo RowItr.h
	g++ -g -std=c++14 -Wall -Werror -c RowElementItr.cpp

clean :
	rm *.o Matrix.out
