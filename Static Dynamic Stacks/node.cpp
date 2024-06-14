#include"node.h"
#include<iostream>
using namespace std;

Node::Node(bool sentinel){
	is_sentinel = sentinel;
	value = -1;
	next = nullptr;
	prev = nullptr;
}

Node::Node(int v, Node* nxt, Node* prv){
	is_sentinel = false;
	value = v;
	next = nxt;
	prev = prv;
}

bool Node::is_sentinel_node(){
	return is_sentinel;
}

int Node::get_value(){
	return value;
}
