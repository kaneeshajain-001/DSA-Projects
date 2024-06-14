#include"stack_b.h"
#include"stack_a.h"
#include<iostream>
#include<stdexcept>
using namespace std;

extern int floor_division(int a, int b);

Stack_B::Stack_B() {
	stk = new int[1024];
	size = 0;
	capacity = 1024;
}

Stack_B::~Stack_B(){
	delete[] stk;
}

void Stack_B::push(int data) {
    if(size >= capacity){
        try{
            int* temp = new int[2 * capacity];
            for (int i = 0; i<size; i++){
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
            capacity *= 2;
        } catch (const bad_alloc& e) {
            throw runtime_error("Out of Memory");
        }
    }
	stk[size] = data;
	size += 1; 
}

int Stack_B::pop() {
    if (size == 0) {
        throw runtime_error("Empty Stack");
    } else {
        int result = stk[size - 1];
        size -= 1;
        if (size <= capacity / 4 && capacity > 1024) {
            int newCapacity = max(capacity / 2, 1024);
            try{
            	int* temp = new int[newCapacity];
            	for (int i = 0; i < size; i++) {
                	temp[i] = stk[i];
            	}
            	delete[] stk;
	            stk = temp;
	            capacity = newCapacity;
			}catch(const bad_alloc&){
				throw runtime_error("Out Of Memory");
			}
        }
        return result;
    }
}


int Stack_B::get_element_from_top(int idx){
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		return (stk[size-idx-1]);
	}
}

int Stack_B::get_element_from_bottom(int idx){
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		return (stk[idx]);
	}
}

void Stack_B::print_stack(bool top_or_bottom){
	if(top_or_bottom){
		for(int i=size-1; i>=0; i--){
			cout<<stk[i]<<endl;
		}
	}else{
		for(int i=0; i<size; i++){
			cout<<stk[i]<<endl;
		}
	}
}

int Stack_B::add(){
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		stk[size] = a+b;
		size += 1;
		return (stk[size-1]);
	}
}

int Stack_B::subtract(){
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		stk[size] = b-a;
		size += 1;
		return (stk[size-1]);
	}
}

int Stack_B::multiply(){
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		stk[size] = a*b;
		size += 1;
		return (stk[size-1]);
	}
}

int Stack_B::divide(){
	if (size<2){
		throw runtime_error("Not Enough Arguments");
	} else{
		int a = pop();
		int b = pop();
		if(a==0){
			throw runtime_error("Divide by Zero Error");
		} else{
			int result = floor_division(a,b);
			push(result);
			return (get_element_from_top(0));
		}
	}
}

int* Stack_B::get_stack(){
	return stk;
}

int Stack_B::get_size(){
	return size;
}

