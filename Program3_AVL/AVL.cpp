//
// Created by xinbochao on 18-5-21.
//
#include <iostream>
#include <queue>
#include "AVL.h"

AVLTree::AVLTree() : BST() {}

void AVLTree::Insert(int key) {
  if(root_ == nullptr) {
    root_ = std::make_shared<BSTNode>(key);
    ++size_;
    return;
  }
  root_ = Insert(root_, key);
}

bool AVLTree::Delete(int key) {
  if(!Find(key))
    return false;

  root_ = Delete(root_, key);
  return true;
}

int AVLTree::DeleteMin() {
  if(root_ == nullptr) {
    std::cerr << "You cannot delete min from an empty tree!" << std::endl;
    return 0; // Not a good idea
  } else {
    int smallestKey = 0;
    root_ = DeleteMin(root_, smallestKey); // size will be substract by 1
    return smallestKey;
  }
}

std::string AVLTree::JSON() const {
  json outputJson;
  outputJson["height"] = Height(root_);
  outputJson["root"] = root_->key_;
  outputJson["size"] = size_;

  std::queue<std::shared_ptr<BSTNode>> q;
  auto temp = root_;

  while(temp != nullptr) {
    std::string nodeKey = std::to_string(temp->key_);
    outputJson[nodeKey] = printNode(temp);

    if(temp->left_ != nullptr)
      q.push(temp->left_);
    if(temp->right_ != nullptr)
      q.push(temp->right_);

    if(q.empty())
      break;
    else {
      temp = q.front();
      q.pop();
    }
  }

  return outputJson.dump(2) + "\n";
}

/*
 * private function after this line
 */

json AVLTree::printNode(std::shared_ptr<BSTNode> node) const {
  json temp;
  temp["height"] = Height(node);
  temp["balance factor"] = node->balanceFactor;

  if(node->left_ != nullptr)
    temp["left"] = node->left_->key_;

  if(node->right_ != nullptr)
    temp["right"] = node->right_->key_;

  auto parentNode = node->parent_.lock();
  if(parentNode != nullptr)
    temp["parent"] = parentNode->key_;
  else
    temp["root"] = true;

  return temp;
}

int AVLTree::Height(std::shared_ptr<BSTNode> node) const {
  if(node == nullptr)
    return -1;
  return node->height;
}

std::shared_ptr<BSTNode> AVLTree::LL_Rotate(std::shared_ptr<BSTNode> node) {
  // LeftChild will be the new root of this tree
  auto LeftChild = node->left_;
  node->left_ = LeftChild->right_;
  if(LeftChild->right_ != nullptr)
    LeftChild->right_->parent_ = node;
  LeftChild->right_ = node;
  LeftChild->parent_ = node->parent_;
  node->parent_ = LeftChild;

  node->height = 1 + std::max(Height(node->left_), Height(node->right_));
  LeftChild->height = 1 + std::max(Height(LeftChild->left_), Height(LeftChild->right_));

  node->balanceFactor = Height(node->right_) - Height(node->left_);
  LeftChild->balanceFactor = Height(LeftChild->right_) - Height(LeftChild->left_);

  return LeftChild;
}

std::shared_ptr<BSTNode> AVLTree::RR_Rotate(std::shared_ptr<BSTNode> node) {
  // RightChild will be the new root of this subtree
  auto RightChild = node->right_;
  node->right_ = RightChild->left_;
  if(RightChild->left_ != nullptr)
    RightChild->left_->parent_ = node;
  RightChild->left_ = node;
  RightChild->parent_ = node->parent_;
  node->parent_ = RightChild;

  node->height = 1 + std::max(Height(node->left_), Height(node->right_));
  RightChild->height = 1 + std::max(Height(RightChild->left_), Height(RightChild->right_));

  node->balanceFactor = Height(node->right_) - Height(node->left_);
  RightChild->balanceFactor = Height(RightChild->right_) - Height(RightChild->left_);

  return RightChild;
}

std::shared_ptr<BSTNode> AVLTree::LR_Rotate(std::shared_ptr<BSTNode> node) {
  node->left_ = RR_Rotate(node->left_);
  node = LL_Rotate(node);
  return node;
}

std::shared_ptr<BSTNode> AVLTree::RL_Rotate(std::shared_ptr<BSTNode> node) {
  node->right_ = LL_Rotate(node->right_);
  node = RR_Rotate(node);
  return node;
}

std::shared_ptr<BSTNode> AVLTree::Insert(std::shared_ptr<BSTNode> node, int key) {
  // base case: node is the leaf
  // we cant set node == nullptr as the base case
  // because we have to assign parent weak_ptr
  if(node == nullptr) {
    ++size_;
    return std::make_shared<BSTNode>(key, node);
  } else {
    if (key < node->key_) {
      node->left_ = Insert(node->left_, key);
      node->left_->parent_ = node;
    }
    else {
      node->right_ = Insert(node->right_, key);
      node->right_->parent_ = node;
    }
  }

  return node = balance(node);
}

// smallestKey is used to return the minimal key being deleted
std::shared_ptr<BSTNode> AVLTree::DeleteMin(std::shared_ptr<BSTNode> node, int &smallestKey) {
  // base case: if node->left is nullptr
  // it means node is the smallest node
  if(node->left_ == nullptr) {
    smallestKey = node->key_;
    auto temp = node->right_;
    node = nullptr;
    --size_;
    return temp;
  } else {
    node->left_ = DeleteMin(node->left_, smallestKey);
  }

  return node = balance(node);
}

std::shared_ptr<BSTNode> AVLTree::Delete(std::shared_ptr<BSTNode> node, int key) {
  // we first perform standard BST deletion
  // we dont need to test whether node is nullptr
  // because we already know that this key exist in the tree
  if(key < node->key_)
    node->left_ = Delete(node->left_, key);
  else if(key > node->key_)
    node->right_ = Delete(node->right_, key);
  else if(node->right_ != nullptr) {
    auto temp = node->right_;
    while(temp->left_ != nullptr) temp = temp->left_; // temp is now the inorder successor of node
    swapNode(node, temp);
    int uselessInt = 0;
    node->right_ = DeleteMin(node->right_, uselessInt);
  } else if(node->left_ != nullptr) {
    auto temp = node->left_;
    while(temp->right_ != nullptr) temp = temp->right_; // temp is now the inorder predecessor of node
    swapNode(node, temp);
    node->left_ = DeleteMax(node->left_);
  } else {
    node = nullptr;
    --size_;
    return node;
  }

  return node = balance(node);
}

std::shared_ptr<BSTNode> AVLTree::balance(std::shared_ptr<BSTNode> node) {

  node->height = 1 + std::max(Height(node->left_), Height(node->right_));
  node->balanceFactor = Height(node->right_) - Height(node->left_);

  // if the tree is unbalance
  // we perform corresponding rotation

  // Left-X case
  if(node->balanceFactor == -2) {
    if(node->left_->balanceFactor > 0)
      node = LR_Rotate(node); // Left-Right case
    else
      node = LL_Rotate(node); // Left-Left case
  } else if(node->balanceFactor == 2) { // Right-X case
    if(node->right_->balanceFactor > 0)
      node = RR_Rotate(node); // Right-Right case
    else
      node = RL_Rotate(node); // Right-Left case
  }

  return node;
}

std::shared_ptr<BSTNode> AVLTree::DeleteMax(std::shared_ptr<BSTNode> node) {
  // base case: if node->left is nullptr
  // it means node is the smallest node
  if(node->right_ == nullptr) {
    auto temp = node->left_;
    node = nullptr;
    --size_;
    return temp;
  } else {
    node->left_ = DeleteMax(node->right_);
  }

  return node = balance(node);
}

void AVLTree::swapNode(std::shared_ptr<BSTNode> a, std::shared_ptr<BSTNode> b) {
  int temp = a->key_;
  a->key_ = b->key_;
  b->key_ = temp;
}

