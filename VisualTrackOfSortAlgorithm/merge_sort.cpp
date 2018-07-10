#include <iostream>
#include <vector>
#include "mergesort.h"

int main() {
	int size = 0, temp = 0;
	std::cin >> size;
	std::vector<int> randomNum;
	for(int i = 0; i < size; ++i) {
		std::cin >> temp;
		randomNum.push_back(temp);
	}
	std::cout << size << std::endl;
	MergeSort(&randomNum);
}
