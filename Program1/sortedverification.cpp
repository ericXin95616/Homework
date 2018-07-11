//
// Created by xinbochao on 18-4-9.
//

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>
#include <string>
#include <vector>

using json = nlohmann::json;

json generateOutput(const json& inputJson, const std::string &fileName);
std::vector<std::vector<int64_t>::const_iterator> findInversion(const std::vector<int64_t> &sampleArray);

std::vector<std::vector<int64_t>::const_iterator> findInversion(const std::vector<int64_t> &sampleArray) {
  std::vector<std::vector<int64_t>::const_iterator> inversionPos;
  for (auto it = sampleArray.begin(); it != sampleArray.end() - 1; ++it) {
    if(*it >= *(it + 1))
      inversionPos.push_back(it);
  }
  return inversionPos;
}

json generateOutput(const json& inputJson, const std::string &fileName) {
  json outputJson;
  int numOfUnsortArray = 0;
  for (auto it = inputJson.cbegin(); it != inputJson.cend() ; ++it) {
    if(it.key() == "metadata") {
      json temp;
      temp["arraySize"] = inputJson["metadata"]["arraySize"];
      temp["file"] = fileName;
      temp["numSamples"] = inputJson["metadata"]["numSamples"];
      temp["samplesWithInversions"] = numOfUnsortArray;
      outputJson["metadata"] = temp;
      continue;
    }

    std::vector<int64_t> sampleArray = it.value();
    std::vector<std::vector<int64_t>::const_iterator> inversionPosition = findInversion(sampleArray);
    /*
     * if inversion position is not empty
     * it means that some consecutive inversion occur
     * and we will add them to outputJson
     */
    if(!inversionPosition.empty()) {
      ++numOfUnsortArray;
      json Sample, consecutiveInversion;
      int numOfInversion = 1;
      for (auto _it = inversionPosition.begin(); _it != inversionPosition.end(); ++_it) {
        std::string numString = std::to_string(numOfInversion);
        consecutiveInversion[numString] = std::vector<int64_t >(*_it, *_it + 2);
        ++numOfInversion;
      }
      Sample["ConsecutiveInversions"] = consecutiveInversion;
      Sample["sample"] = sampleArray;
      outputJson[it.key()] = Sample;
    }
  }
  return outputJson;
}

int main(int argc, char *argv[]) {
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

  json outputJson = generateOutput(inputJson, argv[1]);

  std::cout << std::setw(4) << outputJson << std::endl;
}
