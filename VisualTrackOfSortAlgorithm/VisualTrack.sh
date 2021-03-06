#!/bin/bash
chmod u+x *.sh
javac RandomGeneration.java
java RandomGeneration 100 1 > RandomSample

# find the sort .cpp file
# fileName = 'grep -i *_sort.cpp'

# compile that file
# g++ -g -Wall -Werror -std=c++14 $fileName

make
clear

# fileName = $(find ./*.out)
# echo $(fileName[*])
# redirect input
(./merge_sort.out < RandomSample) > sortProcess.txt

# show visual track
javac VisualTrackOfSortAlgorithm.java
java VisualTrackOfSortAlgorithm < sortProcess.txt
