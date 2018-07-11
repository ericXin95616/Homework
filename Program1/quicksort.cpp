// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


std::pair<int, int> QuickSort(std::vector<int> *numbers) {
   std::pair<int,int> compAccess = std::make_pair(0,0);
   QuickSortRecurse(numbers, 0, numbers->size() - 1, compAccess);
   return compAccess;
}

void QuickSortRecurse(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k, compAccess);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, compAccess);
   QuickSortRecurse(numbers, j + 1, k, compAccess);
   
   return;
}

int Partition(std::vector<int> *numbers, int i, int k, std::pair<int, int> &compAccess) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];
   ++compAccess.second; // added
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
         ++l;
         ++compAccess.second; // added
         ++compAccess.first; // added
      }
      ++compAccess.second; // added
      ++compAccess.first; // added

      /* Decrement h while pivot < numbers[h] */
      while (pivot < (*numbers)[h]) {
         --h;
         ++compAccess.second; // added
         ++compAccess.first; // added
      }
      ++compAccess.second; // added
      ++compAccess.first; // added
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;

         compAccess.second += 4; // added
         ++l;
         --h;
      }
   }
   
   return h;
}
