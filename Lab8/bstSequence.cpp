/*
 * Name: Abigail Poropatich
 * Date Submitted: 3 April 2023
 * Lab Section: 003
 * Assignment Name: Storing a Sequence in a Binary Search Tree (Lab 8)
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "bstSequence.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}
*/

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
    //if T is null, then create a new node
    if(T == nullptr) return new Node(v);
    
    //if the left child of the current node exists
    //then the value of rootRank will be assigned to the size
    //of the left subtree, otherwise 0
    int rootRank = T->left ? T->left->size : 0;

    //insert into the left subtree of the current node
    if(r <= rootRank){
        T->left = insert(T->left, v, r);
        fix_size(T);
    }

    //insert into the right subtree of the current node
    else if(r > rootRank){
        T->right = insert(T->right, v, r-rootRank-1);
        fix_size(T);
    }

    return T;

}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{

    //if T is empty
    if(T == nullptr){
        *L = nullptr;
        *R = nullptr;
    }

    else{
        //if the left child of the current node exists
        //then the value of rootRank will be assigned to the size
        //of the left subtree, otherwise 0
        int rootRank = T->left ? T->left->size : 0;
        int minusOne = rootRank + 1;
        
        //split the left tree
        if(r <= rootRank){
            split(T->left,r,L,&(T->left));
            *R = T;
        }

        //split the right tree
        else if(r > rootRank){
            split(T->right, r - minusOne, &(T->right), R);
            *L = T;
        }

        fix_size(T);
    }
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
  // If (v,r) is the Nth node inserted into T, then:
  // with probability 1/N, insert (v,r) at the root of T
  // otherwise, insert_random (v,r) recursively left or right of the root of T
  
  //if the tree is empty, then create a new node
  if(T == nullptr) return new Node(v);

  else{
    //Number of possible positions to insert the new node
    int rightOps = T->size + 1;

    //Generates a number btw 0 and T->size
    //If that number is 0, insert the new node at the root
    //and split the tree at r
    if(rand() % (rightOps) == 0){
        Node *updateRoot = new Node(v);
        split(T, r, &(updateRoot->left), &(updateRoot->right));
        fix_size(updateRoot);
        return updateRoot;
    }

    //insert recursively to the left
    else{
        int rootRank = T->left ? T->left->size : 0;

        //calculating offset based on left subtree
        int minusOne = rootRank + 1;

        //insert into the left subtree
        if(r <= rootRank){
            T->left = insert_random(T->left, v, r);
        }

        //insert into the right subtree
        else{
            T->right = insert_random(T->right, v, r - minusOne);
        }
        fix_size(T);
    }
  }

  return T;
}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node *T = nullptr;

  // start by inserting the first team
  T = insert_random(T, 0, 0);

  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) // can we insert at beginning?
      T = insert_random(T, i, 0);
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) // can we insert at end?
	    T = insert_random(T, i, T->size);
    else {
	    // 7 5 4 2 0 3 1 6    (when inserting team i=8)
	    // W W W L L L W L

      int left = 0;
      int right = T->size - 1;
      Node* p = nullptr;

      //binary search until the search has been
      //narrowed down to two adjacent nodes
      while(right - left != 1){
        int middle = (left+right) / 2;

        //search left half
        if(did_x_beat_y(i, select(T,middle)->key)) right = middle;
        //search right half
        else left = middle;
      }
      T = insert_random(T, i, right);
    }
  }
  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}