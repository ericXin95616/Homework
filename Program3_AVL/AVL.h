//
// Created by xinbochao on 18-5-21.
//

#ifndef PROGRAM3_AVL_H
#define PROGRAM3_AVL_H

#include "BST.h"
#include <memory>
#include "json.hpp"

using nlohmann::json;

class AVLTree : public BST {
 public:
  AVLTree();

  void Insert(int key) override ;
  bool Delete(int key) override ;
  int DeleteMin() override ;
  std::string JSON() const override ;

  // it will automatically call ~BST()
  // so there is no need to implement it
  ~AVLTree() {}

 private:
  json printNode(std::shared_ptr<BSTNode> node) const;
  int Height(std::shared_ptr<BSTNode> node) const;
  void swapNode(std::shared_ptr<BSTNode> a, std::shared_ptr<BSTNode> b);
  std::shared_ptr<BSTNode> Insert(std::shared_ptr<BSTNode> node, int key);
  std::shared_ptr<BSTNode> DeleteMin(std::shared_ptr<BSTNode> node, int &smallestKey);
  std::shared_ptr<BSTNode> Delete(std::shared_ptr<BSTNode> node, int key);
  std::shared_ptr<BSTNode> balance(std::shared_ptr<BSTNode> node);
  std::shared_ptr<BSTNode> DeleteMax(std::shared_ptr<BSTNode> node);
  std::shared_ptr<BSTNode> LL_Rotate(std::shared_ptr<BSTNode> node);
  std::shared_ptr<BSTNode> RR_Rotate(std::shared_ptr<BSTNode> node);
  std::shared_ptr<BSTNode> LR_Rotate(std::shared_ptr<BSTNode> node);
  std::shared_ptr<BSTNode> RL_Rotate(std::shared_ptr<BSTNode> node);
};

#endif //PROGRAM3_AVL_H
