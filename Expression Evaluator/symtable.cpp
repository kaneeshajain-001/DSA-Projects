/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

int calASCII(string s) {
	int ans = 0;
	int n = s.size();
	for (int i=0; i<n; i++) {
		ans += s[i];
	}
	return ans;
}

SymEntry* successor(SymEntry* want) {
	if (!(want->right)) {
		return want;
	}
	return successor(want->right);
}

SymbolTable::SymbolTable() {
	root = nullptr;
	size = 0;
}

void drastic(SymEntry* node) {
    if(node==nullptr) {
    	return;
	}
   drastic(node->left);
   drastic(node->right);

   delete node;
    
}

SymbolTable::~SymbolTable() {
	drastic(root);
}

void insertHelper(SymEntry*& root, SymEntry* node) {
	if(!root) {
		root = node;
	} else {
		int num1 = calASCII(root->key);
		int num2 = calASCII(node->key);
		if (num1>num2) {
			insertHelper(root->left, node);
		} else {
			insertHelper(root->right, node);
		}
	}
}

void SymbolTable::insert(string k, UnlimitedRational* v) {
	SymEntry* node = new SymEntry(k,v);
	insertHelper(root, node);
	size++;
}

void removeHelper(SymEntry* parent, SymEntry*& child, string k) {
    if (child->key == k) {
        if (child->left) {
            SymEntry* replace = successor(child->left);
            if (calASCII(parent->key) < calASCII(child->key)) {
                parent->right = replace;
            } else {
                parent->left = replace;
            }
            replace->left = child->left;
            replace->right = child->right;
            delete child;
            child = replace;
        } else {
            if (calASCII(parent->key) < calASCII(child->key)) {
                parent->right = child->right;
            } else {
                parent->left = child->right;
            }
            delete child;
            child = nullptr;
        }
    } else {
        int num1 = calASCII(child->key);
        int num2 = calASCII(k);
        if (num1 > num2) {
            removeHelper(child, child->left, k);
        } else {
            removeHelper(child, child->right, k);
        }
    }
}

void SymbolTable::remove(string k) {
	if (root->key == k) {
		if (root->left ) {
			SymEntry* replace = successor(root->left);
			replace->left = root->left;
			replace->right = root->right;
			delete root;
			root = replace;
		} else {
			SymEntry* temp = root->right;
			delete root;
			root = temp;
		}
		size--;
	} else {
		int num1 = calASCII(root->key);
		int num2 = calASCII(k);
		if (num1>num2) {
			removeHelper(root, root->left, k);
		} else {
			removeHelper(root, root->right, k);
		}
	}
	size--;
}

UnlimitedRational* searchHelper(SymEntry* root, string k) {
	if (root->key == k) {
		return root->val;
	} else {
		if (calASCII(root->key)<calASCII(k)) {
			return searchHelper(root->right, k);
		} else {
			return searchHelper(root->left, k);
		}
	}
}

UnlimitedRational* SymbolTable::search(string k) {
	UnlimitedRational* v = searchHelper(root,k);
	return v;
}

int SymbolTable::get_size() {
	return size;
}

SymEntry* SymbolTable::get_root() {
	return root;
}
