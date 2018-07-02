#include "node.h"
#include <math.h>
#include <string>
#define BATCH_SIZE 257

int** iArr = (int**)malloc(sizeof(int*) * BATCH_SIZE);

using namespace std;

node* offset(node* base , int offset) {
	node* res = base;

	for (int i = 0; i < offset; i++) {

		if (!res->next) {
			return NULL;
		}

		res = res->next;
	}

	return res;
}

void init() {
	int k = 0;
	int ag = 0;
	for (int i = 0; i < BATCH_SIZE; i++) {
		if (k > 5) k = 0;
		ag += k;
		iArr[i] = new int(i + ag);
		k++;
	}
}


void setNext(node** arg, node* desc, int p ) {
	node* np = new node();
	node* nnp = np;
	node* pd = desc;
	int plen = p;
	int i = 0;

	while (true) {
		np->downstream = pd;
		np->value = pd->value;

		pd = offset(pd, p);

		if (!pd) {
			break;
		}

		np->next = new node();
		np = np->next;

	}
		
	*arg = nnp;
}

node* initLeafNodes(int** arr, int count, int p) {
	int index = 0;
	int plen = p;

	node* leaf;
	node* op = new node(arr[index]);
	
	leaf = op;

	for (int i = 0; i < count; i += p) {
		if (i + p >= count) {
			plen = i % p;
		}
		
		node* des = new node(arr[index++]);
		op->downstream = des;

		for (int j = 1; j < plen; j++) {
			des->next = new node(arr[index++]);
			des = des->next;
		}

		if (i + p < count) {
			op->next = new node(arr[index]);
			op = op->next;
		}
	}

	return leaf;

}




node* isam(int** arr, int count, int p) {
	node* nk = 0;
	node* rk = 0;

	int plen = p;
	nk = initLeafNodes(arr, count, p);
	
	while(nk->next){
		setNext(&rk, nk, p);
		nk = rk;
	}
	
	return nk;
}

void check(node* root) {

	node* np = root;
	node* leaf = np;
	node* up = root;
	
	bool found = false;
	int i = 1;

	while (np) {
		leaf = np;

		if(!found)
			while (leaf->downstream->downstream) {
				leaf = leaf->downstream;
				i++;
			}
		
		found = true;
		up = leaf;
		leaf = leaf->downstream;

		node* p = leaf;

		while (p) {
			cout << *p->value << endl;
			p = p->next;
		}
		
		np = up->next;
	}
	
	cout << "Depth :: " << to_string(i); 
}
