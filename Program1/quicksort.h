// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

std::pair<int, int> QuickSort(std::vector<int> *numbers);
void QuickSortRecurse(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess);
int Partition(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess);