//
// Created by xinbochao on 18-4-9.
//
#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include <iostream>
#include <fstream>
#include <ctime>

using json = nlohmann::json;
using functionType = decltype(InsertionSort);

void outputCSVFile(const json &input);
void timeCompareAccess(std::vector<int> inputArray, functionType sortFunc);

void timeCompareAccess(std::vector<int> inputArray, functionType sortFunc) {
  clock_t time;
  time = clock();
  std::pair<int, int> compareAndAccess = sortFunc(&inputArray);
  time = clock() - time;
  std::cout << "," << std::fixed << (static_cast<double>(time))/CLOCKS_PER_SEC << "," << compareAndAccess.first << "," << compareAndAccess.second;
}

void outputCSVFile(const json &input) {
  std::cout << "Sample,InsertionSortTime,InsertionSortCompares,"
            << "InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,"
            << "QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;

  for (auto it = input.cbegin(); it != input.cend(); ++it) {
    if(it.key() == "metadata")
      continue;

    std::cout << it.key();
    timeCompareAccess(it.value(), InsertionSort);
    timeCompareAccess(it.value(), MergeSort);
    timeCompareAccess(it.value(), QuickSort);
    std::cout << std::endl;
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << "The number of command line argument is incorrect" << std::endl;
    return 0;
  }

  std::ifstream inputFile;
  inputFile.open(argv[1]);
  if(!inputFile.is_open()) {
    std::cout << "Cannot open the input file" << std::endl;
    return 0;
  }

  json inputJson;
  inputFile >> inputJson;
  outputCSVFile(inputJson);
}