// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"

std::pair<int, int> InsertionSort(std::vector<int>* numbers) {
   unsigned int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   int comparsionTime = 0; // added
   int memaccessTime = 0; // added

   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
         --j;

         ++comparsionTime; // added
         memaccessTime += 6;  // added what if += 4(assignment does not count)
      }

      if(j > 0) {
        ++comparsionTime;
        memaccessTime += 2;
      }
   }
   
   return std::make_pair(comparsionTime, memaccessTime);
}
