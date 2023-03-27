/*
 * Name: Abigail Poropatich
 * Date Submitted:
 * Lab Section: 003
 * Assignment Name: Lab 7: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
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

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  //if the tree is empty then the key does not exist
  if(T == nullptr) return nullptr;

  //if the current node is equal to k
  else if (T->key == k) return T;

  //search in the right tree recursively
  else if(T->key < k) return find(T->right,k);

  //search in the left tree recursively
  else return find(T->left,k);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  //calc # of nodes in the left subtree
  int rank = T->left ? T->left->size : 0;

  //if the rank of T is equal to r
  if(rank == r) return T;

  //if the rank of T is less than r, search right tree recursively
  else if(rank < r){
      int rightRank = r - rank - 1;
      return select(T->right, rightRank);
  }

  //if the rank of T is greater than r, search left tree recursively
  else{
      return select(T->left, r);
  }
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  
  //if one of the trees is empty,
  //return the non empty one
  if(R == nullptr) return L;
  if(L == nullptr) return R;

  //will decide whether R or L will become the new root
  double random = rand() / (R->size + L->size);

  //L will be the root
  if(random < L->size){
    L->right = join(L->right, R);
    fix_size(L);
    return L;
  }

  //R will be the root
  else if(random >= L->size){
    R->left = join(L, R->left);
    fix_size(R);
    return R;
  }

  return nullptr;
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
  
  //Implement Node *remove(Node *T, int k)
  if(T == nullptr) return nullptr;
  if(k == T->key){
    Node *n = join(T->left, T->right);
    delete T;
    return n;
  }

  //remove key from left subtree
  else if(k < T->key){
    T->left = remove(T->left, k);
  }

  //remove from the right subtree
  else{
    T->right = remove(T->right, k);
  }

  //update size
  T->size--;
  fix_size(T);
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{

  //base case
  if(T == nullptr){
    *L = nullptr;
    *R = nullptr;
    return;
  }

  //if k is less than or equal to the key at root T
  if(k < T->key){
    Node **addressL = &(T->left);
    split(T->left, k, L, addressL);
    *R = T;
    fix_size(T);
  }

  //if k is greater than or equal to the key at root T
  else{
    Node **addressR = &(T->right);
    split(T->right, k, addressR, R);
    *L = T;
    fix_size(T);
  }
  fix_size(T);
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  //base case
  if(T == nullptr) return new Node(k);

  int value = rand() % (T->size + 1);

  //if there are no nodes in the right subtree
  //insert at the root
  if(value == 0){
    Node *rooted = new Node(k);
    split(T, k, &(rooted->left), &(rooted->right));
    fix_size(rooted);
    return rooted;
  }

  //if k is in left subtree
  //split T at k
  if(k < T->key) T->left = insert_random(T->left, k);

  //if k is in right subtree
  //split T at k
  else T->right = insert_random(T->right, k);
  
  //update size
  fix_size(T);
  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

// int main(void)
// {
//   vector<int> inorder;
//   vector<int> A(10,0);
  
//   // put 0..9 into A[0..9] in random order
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   cout << "Contents of A (to be inserted into BST):\n";
//   printVector(A);
  
//   // insert contents of A into a BST
//   Node *T = nullptr;
//   for (int i=0; i<10; i++) T = insert(T, A[i]);
  
//   // print contents of BST (should be 0..9 in sorted order)
//   cout << "Contents of BST (should be 0..9 in sorted order):\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);

//   // test select
//   for (int i=0; i<10; i++) {
//     Node *result = select(T, i);
//     if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
//   }

//   // test find: Elements 0..9 should be found; 10 should not be found
//   cout << "Elements 0..9 should be found; 10 should not be found:\n";
//   for (int i=0; i<11; i++) 
//     if (find(T,i)) cout << i << " found\n";
//     else cout << i << " not found\n";

//   // test split
//   Node *L, *R;
//   split(T, 4, &L, &R);
//   cout << "Contents of left tree after split (should be 0..4):\n";
//   inorder=inorder_traversal(L);
//   printVector(inorder);
//   cout << "Left tree size " << L->size << "\n";
//   cout << "Contents of right tree after split (should be 5..9):\n";
//   inorder=inorder_traversal(R);
//   printVector(inorder);
//   cout << "Right tree size " << R->size << "\n";
    
//   // test join
//   T = join(L, R);
//   cout << "Contents of re-joined tree (should be 0..9)\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);
//   cout << "Tree size " << T->size << "\n";
  
//   // test remove
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   for (int i=0; i<10; i++) {
//     T = remove(T, A[i]);
//     cout << "Contents of tree after removing " << A[i] << ":\n";
//     inorder=inorder_traversal(T);
//     printVector(inorder);
//     if (T != nullptr)
//       cout << "Tree size " << T->size << "\n";
//   }

//   // test insert_random
//   cout << "Inserting 1 million elements in order; this should be very fast...\n";
//   for (int i=0; i<1000000; i++) T = insert_random(T, i);
//   cout << "Tree size " << T->size << "\n";
//   cout << "Done\n";
  
//   return 0;
// }
