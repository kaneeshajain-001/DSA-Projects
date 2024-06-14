#include"stack_a.h"
#include<iostream>
#include<stdexcept>
using namespace std;

int floor_division(int a, int b){
	if(b==0){
		return 0;
	} else if(a>0 && b>0 ||a<0 && b<0){
		return b/a;
	} else{
		return (b/a-1);
	}
}

Stack_A::Stack_A() {
	size = 0;
}

void Stack_A::push(int data){
	if(size==1024){
		throw runtime_error("Stack Full");
	} else{
		stk[size] = data;
		size += 1;
	}
}

int Stack_A::pop(){
	if(size==0){
		throw runtime_error("Empty Stack");
	} else{
		int result = stk[size-1];
		size -= 1;
		return result;
	}
}

int Stack_A::get_element_from_top(int idx){
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		return (stk[size-idx-1]);
	}
}

int Stack_A::get_element_from_bottom(int idx){
	if(idx<0 || size<=idx){
		throw runtime_error("Index out of range");
	} else{
		return (stk[idx]);
	}
}

void Stack_A::print_stack(bool top_or_bottom){
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

int Stack_A::add(){
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

int Stack_A::subtract(){
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

int Stack_A::multiply(){
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

int Stack_A::divide(){
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

int* Stack_A::get_stack(){
	return stk;
}

int Stack_A::get_size(){
	return size;
}


