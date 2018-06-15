#include "node.h"
#include <math.h>
using namespace std;

int** iArr = (int**)malloc(sizeof(int*) * 20);


int** slize(node* ns, int count){
  node* n = ns;
  int vsize = sizeof(ns->value);
  int** values = (int**)malloc(sizeof(int*) * count);
  int** vs = values;

  while(n){
    *vs = &(n->value);
    vs++;
    n = n->next;
  }

  return values;
}

node* init(){
  node* n = new node();
  node* res = n;
  for(int i = 0; i < 20; i++){
    iArr[i] = new int(i);
    n->value = iArr[i];

    if ( i != 20 - 1){
      n->next = new node();
      n = n->next;
    }
  }
  return res;
}


void setNext(node** arg, int** vArr , int count){
  node* np = new node();
  node* nnp = np;

  for(int i = 0; i < count; i++){
    if( !(vArr + i) ){
      break;
    }

    np->value = *vArr[i];

    if (i != count - 1){
      np->next = new node();
      np = np->next;
    }
  }

  *arg = nnp;
}

node* isam(int** arr, int count, int p){
  int** slized = arr;
  int plen = count;

  node* op;

  while(plen != 1){
    op = setUpStream(slized, plen, p);
    plen = ceil(plen / p);
    slized = slize(op,plen);
  }

  return op;
}


node* setUpStream(int** arr, int count, int p){
  node* nk = new node();
  node* rk;
  node* nkk = nk;

  for (int i = 0; i < count; arr += p, i += p ){

    setNext(&rk,arr,p);
    nk->downstream = rk;
    nk->value = rk->value;

    if(i != count - p){
      nk->next = new node();
      nk = nk->next;
    }
  }

  return nkk;
}


int main(){
  init();
  node* root = isam(iArr, 20, 4);
  return 0;
}
