#include <iostream>
#include <vector>

using std::vector;

void readStack(vector<int>& stackOfInt, int stackSize) {
  int temp = 0;
  for (int i = 0; i < stackSize; ++i) {
    std::cin >> temp;
    stackOfInt.push_back(temp);
  }
}

void addTwoEntries(vector<int> &stackOfInt) {
  for(size_t i = 0, size = stackOfInt.size(); i < size - 1; ++i) {
    stackOfInt[size - i - 2] = stackOfInt[size - i - 2] + stackOfInt[size - i - 1];
  }
  for(size_t i = 0; i < stackOfInt.size(); ++i) {
    std::cout << stackOfInt[i] << " ";
  }
  std::cout << std::endl;
}

/*
 * this binary Search is for this program only
 */
bool binarySearch(const vector<int> &stackOfInt, int target, size_t lowerbound, size_t upperbound) {
  if(lowerbound == upperbound)
    return stackOfInt[lowerbound] == target;

  size_t middlepoint = (lowerbound + upperbound) / 2;

  if(stackOfInt[middlepoint] > target) {
    return binarySearch(stackOfInt, target, middlepoint + 1, upperbound);
  } else if(stackOfInt[middlepoint] < target){
    return binarySearch(stackOfInt, target, lowerbound, middlepoint);
  } else if(stackOfInt[middlepoint] == target) {
    return true;
  }
  return false;
}

int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) {
  /*
   * Write your code here.
   */
  addTwoEntries(h1);
  addTwoEntries(h2);
  addTwoEntries(h3);
  for (size_t i = 0, size = h1.size(); i < size; ++i) {
    if(binarySearch(h2, h1[i], 0, h2.size() - 1) && binarySearch(h3, h1[i], 0, h3.size() - 1))
      return h1[i];
  }
  return 0;
}

int main() {
  int stackSize1 = 0, stackSize2 = 0, stackSize3 = 0;
  std::cin >> stackSize1 >> stackSize2 >> stackSize3;
  vector<int> stack1, stack2, stack3;
  readStack(stack1, stackSize1);
  readStack(stack2, stackSize2);
  readStack(stack3, stackSize3);
  std::cout << equalStacks(stack1, stack2, stack3) << std::endl;
  return 0;
}