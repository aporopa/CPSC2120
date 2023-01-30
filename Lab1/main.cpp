#include <iostream>
#include "ListStack.h"
#include "ListQueue.h"

using namespace std;

int main()
{
   ListQueue<int> queue;
  bool is_empty = queue.empty();

  if (is_empty) {
    cout << "The queue is empty" << endl;
  } else {
    cout << "The queue is not empty" << endl;
  }
  
    return 0;
}