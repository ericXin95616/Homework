// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

std::pair<int,int> MergeSort(std::vector<int>* numbers) {
   std::pair<int,int> compAccess = std::make_pair(0,0);
   MergeSortRecurse(numbers, 0, numbers->size() - 1, compAccess);
   return compAccess;
}


void MergeSortRecurse(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, compAccess);
      MergeSortRecurse(numbers, j + 1, k, compAccess);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, compAccess);
   }
}

void Merge(std::vector<int> *numbers, int i, int j, int k, std::pair<int, int> &compAccess) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         ++rightPos;
         
      }
      ++compAccess.first; // added
      compAccess.second += 4; // added
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      ++leftPos;
      ++mergePos;

      compAccess.second += 2; // added
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      ++rightPos;
      ++mergePos;

      compAccess.second += 2; // added
   }
   
   // Copy merge number back to numbers
   compAccess.second += 2*mergedSize; // added
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
   }
}
