//
// Created by xinbochao on 18-4-9.
//
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using json = nlohmann::json;

json compareJson(const json &lhs, const json &rhs, const std::string &fileName1, const std::string &fileName2);
json generateMetadata(const json &lhsMeta,
                      const json &rhsMeta,
                      const std::string &fileName1,
                      const std::string &fileName2,
                      int numOfConflictResult);
json generateMismatch(const std::vector<std::pair<int64_t, int64_t>> &conflictPosition);
std::vector<std::pair<int64_t, int64_t>> findConfliction(const std::vector<int64_t> &lhsVec,
                                                         const std::vector<int64_t> &rhsVec);

json generateMetadata(const json &lhsMeta,
                      const json &rhsMeta,
                      const std::string &fileName1,
                      const std::string &fileName2,
                      int numOfConflictResult) {
  json metadata, file1, file2;
  // create file1
  file1["arraySize"] = lhsMeta["arraySize"];
  file1["numSamples"] = lhsMeta["numSamples"];
  file1["name"] = fileName1;
  // create file2
  file2["arraySize"] = rhsMeta["arraySize"];
  file2["numSamples"] = rhsMeta["numSamples"];
  file2["name"] = fileName2;
  //create metadata
  metadata["File1"] = file1;
  metadata["File2"] = file2;
  metadata["samplesWithConflictingResults"] = numOfConflictResult;
  return metadata;
}

json generateMismatch(const std::vector<std::pair<int64_t, int64_t>> &conflictPosition) {
  json mismatch;
  int numOfMismatch = 0;
  for (auto it = conflictPosition.cbegin(); it != conflictPosition.cend() ; ++it) {
    std::string numString = std::to_string(numOfMismatch++);
    std::vector<int64_t> temp;
    temp.push_back(it->first);
    temp.push_back(it->second);
    mismatch[numString] = temp;
  }
  return mismatch;
}

std::vector<std::pair<int64_t, int64_t>> findConfliction(const std::vector<int64_t> &lhsVec,
                                                         const std::vector<int64_t> &rhsVec) {
  std::vector<std::pair<int64_t, int64_t>> conflictPos;
  auto lhsVecIt = lhsVec.cbegin(), rhsVecIt = rhsVec.cbegin();
  // suppose lhsVec and rhsVec have the same size
  for (; lhsVecIt != lhsVec.cend() ; ++lhsVecIt, ++rhsVecIt) {
    if(*lhsVecIt != *rhsVecIt)
      conflictPos.emplace_back(std::make_pair(*lhsVecIt, *rhsVecIt));
  }
  return conflictPos;
}
/*
 * what if left json and right json have a different size
 */
json compareJson(const json &lhs, const json &rhs, const std::string &fileName1, const std::string &fileName2) {
  json outputJson;

  // suppose lhs and rhs have the same size
  int numOfDifferentSample = 0;
  for (auto lhsIt = lhs.cbegin(), rhsIt = rhs.cbegin(); lhsIt != lhs.cend() ; ++lhsIt, ++rhsIt) {
    if(lhsIt.key() == "metadata") {
      outputJson["metadata"] = generateMetadata(lhsIt.value(), rhsIt.value(), fileName1, fileName2, numOfDifferentSample);
      //outputJson["samplesWithConflictingResults"] = numOfDifferentSample;
      continue;
    }

    std::vector<int64_t> lhsVec = lhsIt.value();
    std::vector<int64_t> rhsVec = rhsIt.value();
    std::vector<std::pair<int64_t, int64_t>> conflictPosition = findConfliction(lhsVec, rhsVec);

    if(!conflictPosition.empty()) {
      ++numOfDifferentSample;
      json temp, mismatch;
      temp[fileName1] = lhsIt.value();
      temp[fileName2] = rhsIt.value();
      temp["Mismatches"] = generateMismatch(conflictPosition);
      outputJson[lhsIt.key()] = temp;
    }
  }

  return outputJson;
}

int main(int argc, char *argv[]) {
  if(argc != 3) {
    std::cout << "The number of command line argument is incorrect" << std::endl;
    return 0;
  }

  std::ifstream inputFile1(argv[1]), inputFile2(argv[2]);
  if(!inputFile1.is_open() || !inputFile2.is_open()) {
    std::cout << "Fail to open the file" << std::endl;
    return 0;
  }
  json inputJson1, inputJson2;
  inputFile1 >> inputJson1;
  inputFile2 >> inputJson2;

  json outputJson = compareJson(inputJson1, inputJson2, argv[1], argv[2]);

  std::cout << std::setw(4) << outputJson << std::endl;
}


