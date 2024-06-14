/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    par = nullptr;
    left = nullptr;
    right = nullptr;
}

SymNode::SymNode(string k){
	key = k;
    par = nullptr;
	left = nullptr;
    right = nullptr;
}

SymNode* SymNode::LeftLeftRotation(){
	SymNode *y = this->right; 
    SymNode *T2 = y->left; 
    y->left = this; 
    this->right = (T2 ? T2 : nullptr);
    this->height = 1 + std::max(this->left ? this->left->height : 0, this->right ? this->right->height : 0);
    y->height = 1 + std::max(y->left ? y->left->height : 0, y->right ? y->right->height : 0);
    return y;
}

SymNode* SymNode::RightRightRotation(){
	SymNode *x = this->left; 
    SymNode *T2 = x->right;
    x->right = this; 
    this->left = (T2 ? T2 : nullptr); 
    this->height = 1 + std::max(this->left ? this->left->height : 0, this->right ? this->right->height : 0);
    x->height = 1 + std::max(x->left ? x->left->height : 0, x->right ? x->right->height : 0);
    return x; 
}

SymNode* SymNode::LeftRightRotation(){
	this->left = this->left->LeftLeftRotation();
	return this->RightRightRotation();
}

SymNode* SymNode::RightLeftRotation(){
	this->right = this->right->RightRightRotation();
	return this->LeftLeftRotation();
}

SymNode::~SymNode(){
	delete left;
	delete right;
}
