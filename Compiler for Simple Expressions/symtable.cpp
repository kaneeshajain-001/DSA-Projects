/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

int get_balance(SymNode* node) {
    int leftH = 0, rightH = 0;
    if (node->left) {
        leftH = node->left->height;
    }
    if (node->right) {
        rightH = node->right->height;
    }
    return (leftH - rightH);
}


SymbolTable::SymbolTable(){
	root = nullptr;
	size = 0;
}

SymNode* insertHelper(string k, SymNode* node) {
    if (!node) {
        node = new SymNode(k);
    } else if (k < node->key) {
        node->left = insertHelper(k, node->left);
    } else if (k > node->key) {
        node->right = insertHelper(k, node->right);
    }
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
    return node; 
}


void SymbolTable::insert(string k){
	root = insertHelper(k, root);
	if (get_balance(root)>1) {
		if (k < root->left->key) {
			root = root->RightRightRotation();
		} 
		else {
            root = root->LeftRightRotation();
        } 
	} else if (get_balance(root)<-1) {
		if (k < root->right->key) {
			root = root->RightLeftRotation();
		} 
		else {
            root = root->LeftLeftRotation();
        } 
	}
	size++;
}

SymNode* predecessor(SymNode* node) {
	SymNode* current = node;
	while (current->left != nullptr) {
		current = current->left; 
	}
    return current; 
}
 
SymNode* deleteHelper(SymNode* root, string k) {
	if (!root) {
		return root;
	}
	if (k < root->key) {
		root->left = deleteHelper(root->left, k); 
	} else if (k > root->key) {
		root->right = deleteHelper(root->right, k); 
	} else {
		if ((root->left == nullptr) || (root->right == nullptr)) { 
            SymNode *temp = (root->left ? root->left : root->right); 
            if (temp == nullptr) {
            	temp = root;
            	root = nullptr;
			} else {
				root = temp;
			}
        }  else {
        	SymNode* temp = predecessor(root->right); 
        	root->key = temp->key;
        	root->right = deleteHelper(root->right, temp->key); 
		}
	}
	
    if (root == nullptr) {
    	return root;
	} 
	root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
    int balance = get_balance(root);
    if (balance > 1) {
    	if (get_balance(root->left)>=0) {
    		root = root->RightRightRotation();
		} else {
			root = root->LeftRightRotation();
		}
	} else if (balance < -1) {
		if (get_balance(root->right)<=0) {
    		root = root->LeftLeftRotation();
		} else {
			root = root->RightLeftRotation();
		}
	} 
    return root; 
}

void SymbolTable::remove(string k) {
	root = deleteHelper(root, k);
	size--;
}

int searchHelper(SymNode* root, string k) {
	if (!root) {
		return -2;
	}
	if (root->key == k) {
		return root->address;
	} else {
		if (root->key < k) {
			return searchHelper(root->right, k);
		} else {
			return searchHelper(root->left, k);
		}
	}
}

int SymbolTable::search(string k) {
	int v = searchHelper(root,k);
	return v;
}

void assignHelper(string k, int idx, SymNode* node) {
	if (node->key == k) {
		node->address = idx;
		return;
	} else {
		if (node->key<k) {
			return assignHelper(k, idx, node->right);
		} else {
			return assignHelper(k, idx, node->left);
		}
	}
}
void SymbolTable::assign_address(string k, int idx){
	assignHelper(k,idx,root);
}

int SymbolTable::get_size(){
	return size;
}

SymNode* SymbolTable::get_root(){
	return root;
}

void drastic(SymNode* node) {
    if (node == nullptr) {
    	return;
	}
   drastic(node->left);
   drastic(node->right);

   delete node;
    
}

SymbolTable::~SymbolTable() {
	drastic(root);
}
