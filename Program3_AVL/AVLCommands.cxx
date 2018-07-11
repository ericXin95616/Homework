//
// Created by xinbochao on 18-5-22.
//

#include "json.hpp"
#include "AVL.h"
#include <iostream>
#include <fstream>

using nlohmann::json;

void BuildTree(AVLTree &avlTree, const json &AVLOperations) {
  for (json::const_iterator it = AVLOperations.begin(), end = AVLOperations.end(); it != end ; ++it) {
    if(it.key() == "metadata")
      continue;

    if((*it)["operation"] == "Insert") {
      avlTree.Insert((*it)["key"]);
    } else if((*it)["operation"] == "Delete") {
      avlTree.Delete((*it)["key"]);
    } else if((*it)["operation"] == "DeleteMin") {
      avlTree.DeleteMin();
    }

    std::cout << avlTree.JSON() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "The number of command line argument is incorrect" << std::endl;
    return 0;
  }

  json AVLOperations;
  std::ifstream inputFiles(argv[1]);
  inputFiles >> AVLOperations;
  AVLTree avlTree;

  BuildTree(avlTree, AVLOperations);

  std::cout << avlTree.JSON();
}