#ifndef BST_H
#define BST_H

#include <memory>
#include <string>


class BST;
class AVLTree;

class BSTNode {
 public:
 	BSTNode(int key);
 	BSTNode(int key, std::weak_ptr<BSTNode> parent);
 	bool IsLeaf() const;
 	bool IsMissingChild() const;
 	bool HasLeftChild() const;
 	bool HasRightChild() const;
 	void DeleteChild(std::shared_ptr<BSTNode> v);
 	void ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u);

 private:
  int key_;
  int height;
  int balanceFactor;
  std::weak_ptr<BSTNode> parent_;
  std::shared_ptr<BSTNode> left_;
  std::shared_ptr<BSTNode> right_;

  friend class BST;
  friend class AVLTree;
}; // class BSTNode

class BST {
 public:
 	BST();

 	virtual void Insert(int key);
 	virtual bool Delete(int key);
 	bool Find(int key) const;
 	virtual std::string JSON() const;
 	size_t size() const;
 	bool empty() const;
 	virtual int DeleteMin();

    virtual ~BST();
 private:
	void DeleteLeaf(std::shared_ptr<BSTNode> currentNode);
	int DeleteMin(std::shared_ptr<BSTNode> currentNode);
    void deleteTree(std::shared_ptr<BSTNode> node);

 	std::shared_ptr<BSTNode> root_;
 	size_t size_;

  friend class AVLTree;
}; // class BST

# endif