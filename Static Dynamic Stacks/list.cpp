#include "list.h"
#include "node.h"
#include <iostream>
using namespace std;


List::List() {
    sentinel_head = new Node();
    sentinel_tail = new Node();
    sentinel_head->next = sentinel_tail; 
    sentinel_tail->prev = sentinel_head;
    sentinel_tail->next = sentinel_head;
    sentinel_head->prev = sentinel_tail;
    size = 0;
}

List::~List() {
    while(size>0){
    	delete_tail();
	}
	delete sentinel_head;
	delete sentinel_tail;
}

void List::insert(int v) {
    Node* end = sentinel_tail->prev;
    Node* temp = new Node(v, sentinel_tail, end);
    end->next = temp;
    sentinel_tail->prev = temp;

    size += 1;
}

int List::delete_tail(){
	Node* end = sentinel_tail->prev;
	int result = end->get_value();
	end->prev->next = sentinel_tail;
	sentinel_tail->prev = end->prev;
	delete end;
	size -= 1;
	return result;
}

int List::get_size(){
	return size;
}

Node* List::get_head(){
	return sentinel_head;
}

