// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

std::pair<int,int> MergeSort(std::vector<int>* numbers);
void MergeSortRecurse(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess);
void Merge(std::vector<int> *numbers, int i, int j, int k, std::pair<int, int> &compAccess);