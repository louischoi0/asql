#include <stdlib.h>
#include <iostream>

using namespace std;

struct node{
  struct node* downstream;
  struct node* next;

  int value;
};


int **slize(node* ns, int count);
void setNext(node** arg, int** vArr , int count);
node* setUpStream(int** arr, int count, int p);
