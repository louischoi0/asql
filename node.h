#ifndef __NODE__
#define __NODE__

#include <stdlib.h>
#include <iostream>

using namespace std;

template <class T>
struct oned_list {
	T* element;
	oned_list<T>* next;

	oned_list(T& e) {
		this->element = &e;
		this->next = 0;
	}

	oned_list() {
		this->element = 0;
		this->next = 0;
	}
};


template <class T>
struct oned_list<T>* link(oned_list<T>& list, T& e) {
	if (!list.next) {
		list.next = new oned_list<T>(e);
		return list.next;
	}

	else {
		cout << "Next Elment Occupied" << endl;
		return 0;
	}
}

struct node {
	struct node* downstream;
	struct node* next;

	int* value;
	
	node() {
		this->downstream = 0;
		this->next = 0;
		this->value = 0;
	};
	node(int* n) {
		this->next = 0;
		this->downstream = 0;
		this->value = n;
	}


};
void check(node*);
void setNext(node** , node** , int count);

#endif