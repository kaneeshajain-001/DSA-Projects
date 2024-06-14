#include"node.h"
#include"list.h"
#include"stack_c.h"
#include"stack_a.h"
#include <iostream>
#include <stdexcept>
using namespace std;

extern int floor_division(int a, int b);

Stack_C::Stack_C(){
	try{
		stk = new List();
	}catch(const bad_alloc&){
		throw runtime_error("Out Of Memory");
	}
}

Stack_C::~Stack_C(){
	delete stk;
}

void Stack_C::push(int data){
	stk->insert(data);
}

int Stack_C::pop(){
	if(stk->get_size()==0){
		throw runtime_error("Empty Stack");
	}else{
		return stk->delete_tail();
	}
}

int Stack_C::get_element_from_top(int idx){
	int size = stk->get_size();
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		Node* current = stk->get_head();
		int size = stk->get_size();
		for(int i=0; i<size-idx; i++){
			current = current->next;
		}
		return (current->get_value());
	}
}

int Stack_C::get_element_from_bottom(int idx){
	int size = stk->get_size();
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		Node* current = stk->get_head();
		for(int i=0; i<=idx; i++){
			current = current->next;
		}
		return (current->get_value());
	}
}

void Stack_C::print_stack(bool top_or_bottom){
	int size = stk->get_size();
	if(top_or_bottom){
		Node* tail = stk->get_head()->prev;
		Node* current = tail->prev;
		while(current->is_sentinel_node()==false){
			cout<<current->get_value()<<endl;
			current = current->prev;
		}
	}else{
		Node* current = stk->get_head()->next;
		while(current->is_sentinel_node()==false){
			cout<<current->get_value()<<endl;
			current = current->next;
		}
	}
}

int Stack_C::add(){
	int size = stk->get_size();
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		push(a+b);
		return (get_element_from_top(0));
	}
}

int Stack_C::subtract(){
	int size = stk->get_size();
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		push(b-a);
		return (get_element_from_top(0));
	}
}

int Stack_C::multiply(){
	int size = stk->get_size();
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		push(a*b);
		return (get_element_from_top(0));
	}
}

int Stack_C::divide(){
	int size = stk->get_size();
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		if(a==0){
			throw runtime_error("Divide by Zero Error");
		}else{
			int result = floor_division(a,b);
			push(result);
			return (get_element_from_top(0));
		}
	}
}

List* Stack_C::get_stack(){
	return stk;
}

int Stack_C::get_size(){
	return stk->get_size();
}
