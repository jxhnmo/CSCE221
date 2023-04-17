#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
private: // this private BinaryNode is within BST
  struct BinaryNode
  {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    bool status; // status = 0 if the node belongs to the tree with root r1 (it can also be in the tree with root r2);
    // status = 1 means that the node only belongs to the tree with root r2

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, bool st)
        : element(theElement), left(lt), right(rt), status(st)
    {
    }
  };

  BinaryNode *r1; // r1 is the root of the BST for the persistent dynamic set
  BinaryNode *r2;

  /**
   * Internal method to insert into a subtree.
   * x is the item to insert.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   * if st=0, insert an element from the persistent dynamic set; st=1,otherwise
   */
  void insert(const Comparable &x, BinaryNode *&t, bool st)
  {
    // impplement here
    if (st == 0)
    {
      BinaryNode *cursor = t;
      BinaryNode *y = nullptr;
      while (cursor)
      {
        y = cursor;
        if (x < cursor->element)
          cursor = cursor->left;
        else
          cursor = cursor->right;
      }

      BinaryNode *newNode = new BinaryNode(x, nullptr, nullptr, st);
      if (y == nullptr)
        t = newNode;
      else if (x < y->element)
        y->left = newNode;
      else
        y->right = newNode;
    }
    else
    {
      if (!t && r1)
      {
        t = new BinaryNode(r1->element, r1->left, r1->right, st);
      }

      if (x > t->element)
      {
        if (t->right == nullptr)
          t->right = new BinaryNode(x, nullptr, nullptr, st);
        else
        {
          t->right = new BinaryNode(t->right->element, t->right->left, t->right->right, st);
          insert(x, t->right, st);
        }
      }
      else
      {
        if (t->left == nullptr)
          t->left = new BinaryNode(x, nullptr, nullptr, st);
        else
        {
          t->left = new BinaryNode(t->left->element, t->left->left, t->left->right, st);
          insert(x, t->left, st);
        }
      }
    }
  }

  /**
   * Internal method to remove from a subtree.
   * x is the item to remove.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   * this function is only for the elements not in the persistent dynamic set
   */
  void remove(const Comparable &x, BinaryNode *&t)
  {
    // implement here
    if (t == nullptr)
      return;
    if (x < t->element)
      remove(x, t->left);
    else if (x > t->element)
      remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr)
    {
      BinaryNode *minRight = t->right;
      while (minRight->left != nullptr)
        minRight = minRight->left;

      t->element = minRight->element;
      t->status = minRight->status;

      remove(t->element, t->right);
    }
    else if (t->status != 0)
    {
      BinaryNode *oldNode = t;
      t = (t->left != nullptr) ? t->left : t->right;
      delete oldNode;
    }
  }

  /**
   * Internal method to make subtree empty.
   * if st = 1, 't' is a node in the tree with root r2; otherwise,
   * 't' is a node in the tree with root r1
   * think about how to deal with 't' if 't' is a common node of the two
   * trees
   */
  void makeEmpty(BinaryNode *&t, bool st)
  {
    // implement here

    if (t == nullptr)
      return;

    makeEmpty(t->left, st);
    makeEmpty(t->right, st);

    if (t->status == st || st == 0)
    {
      if (t->left != nullptr)
      {
        t->left->status = t->status;
      }
      if (t->right != nullptr)
      {
        t->right->status = t->status;
      }
      delete t;
    }
    else if (t->status == 0 && st == 1)
    {
      BinaryNode *newNode = new BinaryNode(t->element, nullptr, nullptr, 0);
      t->status = 1;
      newNode->left = t;
      newNode->status = 1;
      t = newNode;
    }
    else
    {
      BinaryNode *newNode = new BinaryNode(t->element, nullptr, nullptr, 0);
      t->status = 0;
      newNode->right = t;
      newNode->status = 1;
      t = newNode;
    }
  }

  /**
   * Internal method to clone subtree.
   * if st = 1, t is a node in the BST with root r1;
   * if st = 0, otherwise
   */
  BinaryNode *clone(BinaryNode *t, bool st) const
  {
    // implement here
    if (t == nullptr)
      return nullptr;
    else
    {
      BinaryNode *leftClone = clone(t->left, st);
      BinaryNode *rightClone = clone(t->right, st);
      BinaryNode *result = new BinaryNode(t->element, leftClone, rightClone, t->status);
      return result;
    }
  }

public:
  BinarySearchTree() : r1(NULL), r2(NULL)
  {
  }

  BinarySearchTree(const BinarySearchTree &rhs)
  {
    *this = rhs;
  }

  /**
   * Destructor for the tree
   */
  ~BinarySearchTree()
  {
    makeEmpty();
  }

  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable &findMin(BinaryNode *t) const
  {
    if (t == nullptr)
      throw underflow_error("UnderflowException");

    while (t != nullptr)
    {
      t = t->left;
    }
    return t->element;
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable &findMax(BinaryNode *t) const
  {
    if (t == nullptr)
      throw underflow_error("UnderflowException");

    while (t != nullptr)
    {
      t = t->right;
    }
    return t;
  }

  /**
   * Returns true if x is found in the subtree with root t.
   */
  bool contains(const Comparable &x, BinaryNode *t) const
  {
    if (t == nullptr)
      return false;
    else if (x < t->element)
      return contains(x, t->left);
    else if (x > t->element)
      return contains(x, t->right);
    else
      return true;
  }

  /**
   * returns the node with element = x in the subtree with root t
   * to make sure that x is always here, call contains(x, t) first
   */

  BinaryNode *search(const Comparable &x, BinaryNode *t) const
  {
    if (contains(x, t))
    {
      if (x < t->element)
        return search(x, t->left);
      else if (x > t->element)
        return search(x, t->right);
    }
    return t;
  }

  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty() const
  {
    return r1 == NULL;
  }

  /**
   * Make the tree logically empty.
   * remove all items
   * pay attention to the common nodes in r1 and r2
   */
  void makeEmpty()
  {
    makeEmpty(r2, 1);
    makeEmpty(r1, 0);
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   * if st =0, insert into the tree with root r1; if st=1, insert into the
   * tree with root r2
   */
  void insert(const Comparable &x, bool st)
  {
    // implement here
    if (st == 0)
    {
      insert(x, r1, st);
    }
    else
    {
      insert(x, r2, st);
    }
  }

  /**
   * Remove x from the tree with root r2. Nothing is done if x is not found
   * or if x is from the persistent dynamic set.
   */
  void remove(const Comparable &x)
  {
    // implement here
    remove(x, r2);
  }

  /**
   * Deep copy.
   * notice the common nodes in both trees
   */

  const BinarySearchTree &operator=(const BinarySearchTree &rhs)
  {
    if (this != &rhs)
    {
      makeEmpty();
      r1 = clone(rhs.r1, 0);
      r2 = clone(rhs.r2, 1);
    }
    return *this;
  }

  /* in-order tree walk and the result is stored in v
   * the root is r
   */

  void inOrder(vector<BinaryNode *> &v, BinaryNode *r)
  {
    // implement here
    if (r == nullptr)
      return;
    inOrder(v, r->left);
    v.push_back(r);
    inOrder(v, r->right);
  }

  /* this function is to test
   * please do not change
   */
  void printTree() // Print tree in sorted order
  {
    vector<BinaryNode *> v1, v2;

    inOrder(v1, r1); // inorder traverse
    inOrder(v2, r2); // inorder traverse

    cout << "print BST for persistent dynamic set   " << endl;

    int i, j;
    for (i = 0; i < v1.size(); i++)
    {
      cout << v1.at(i)->element << "  ";
    }
    cout << endl;

    cout << "print BST for the whole input set   " << endl;

    for (i = 0; i < v2.size(); i++)
    {
      cout << v2.at(i)->element << "  ";
    }
    cout << endl;

    i = 0;
    j = 0;

    // output the common nodes with the same address in both trees
    // a common node in both trees must have the same address
    cout << "Common nodes: ";
    while (i < v1.size())
    {
      if (v1.at(i)->element == v2.at(j)->element)
      {
        if (v1.at(i) == v2.at(j)) // if the address are equal
        {
          cout << v1.at(i)->element << "  ";
        }

        i++;
        j++;
      }
      else if (v2.at(j)->element < v1.at(i)->element)
        j++;
    }
    cout << endl;
  }
};

#endif
