#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
class node {
	
	public:
		char color;
		int count;
		string word;
		node* left;
		node* right;
		node* par;
		
		node(string s, char c) {
			word = s;
			color = c;
			left = nullptr;
			right = nullptr;
		}
};

class RBTree {
	
	private:
		int compare1(string s1, string s2) {
			string c1, c2;
			for (char c : s1) {
				c1 += std::tolower(c);
			}
			for (char c : s2) {
				c2 += std::tolower(c);
			}
			if (c1 == c2) {
				return 0;
			}
			int size = std::min(s1.size(), s2.size()); 
			for (int i=0; i<size; i++) {
				if (c1[i] > c2[i]) {
					return 1;
				} else if (c1[i] < c2[i]) {
					return -1;
				}
			}
			if (c1.size()>c2.size()) {
				return 1;
			} else {
				return -1;
			}
		}
		
		void LeftRotate(node* x) {
	        node* y = x->right;
	        node* T2 = y->left;
	        x->right = T2;
	        if (T2) {
	        	T2->par = x;
			}
	            
	        y->par = x->par;
	        if (x->word == root->word) {
	        	root = y;
			} else if (x == x->par->left) {
				x->par->left = y;
			} else {
				x->par->right = y;
			} 
	        y->left = x;
	        x->par = y;
	    }
	    
	    void RightRotate(node* y) {
	        node* x = y->left;
	        node* T2 = x->right;
	        y->left = T2;
	        if (T2)
	            T2->par = y;
	        x->par = y->par;
	        if (y->word == root->word) {
	        	root = x;
			} else if (y == y->par->left) {
				y->par->left = x;
			} else {
				y->par->right = x;
			}
	        x->right = y;
	        y->par = x;
	    }
		
		void InsertHelper(node* n) {
			if (n->par->color == 'b') {
				return;
			}
			while ((n->par != nullptr) and (n->par->color == 'r')) {
				if (n->par->par) {
					if (n->par == n->par->par->left) {
		                node* sibling = n->par->par->right;
		                if (sibling) {
		                	if (sibling->color == 'r') {
			                    n->par->color = 'b';
			                    sibling->color = 'b';
			                    n->par->par->color = 'r';
			                    n = n->par->par;
			                    if (n->word == root->word) {
			                    	break;
								}
			                } else {
			                    if (n == n->par->right) {
			                        n = n->par;
			                        LeftRotate(n);
			                    }
			                    n->par->color = 'b';
			                    n->par->par->color = 'r';
			                    RightRotate(n->par->par);
			                }
						} else {
							if (n == n->par->right) {
		                        n = n->par;
		                        LeftRotate(n);
		                    }
		                    n->par->color = 'b';
		                    n->par->par->color = 'r';
		                    RightRotate(n->par->par);
						}
		                
		            } else {
		                node* sibling = n->par->par->left;
		                if (sibling) {
		                	if (sibling->color == 'r') {
			                    n->par->color = 'b';
			                    sibling->color = 'b';
			                    n->par->par->color = 'r';
			                    n = n->par->par;
			                    if (n->word == root->word) {
			                    	break;
								}
			                } else {
			                    if (n == n->par->left) {
			                        n = n->par;
			                        RightRotate(n);
			                    }
			                    n->par->color = 'b';
			                    n->par->par->color = 'r';
			                    LeftRotate(n->par->par);
			                }
						} else {
							if (n == n->par->left) {
		                        n = n->par;
		                        RightRotate(n);
		                    }
		                    n->par->color = 'b';
		                    n->par->par->color = 'r';
		                    LeftRotate(n->par->par);
						}
		            }
				} else {
					break;
				}
			}
			root->color = 'b';
		}
	
	public:
		node* root;
		
		RBTree() {
			root = nullptr;
		}
		
		void insert(node* newNode){
			newNode->count = 1;
			node* current = root;
			node* parent = root;
			while (current) {
				if (compare1(newNode->word, current->word) == 1) {
					parent = current;
					current = current->right;
				} else {
					parent = current;
					current = current->left;
				}
			}
			current = newNode;
			current->par = parent;
			if (compare1(current->word, parent->word) == 1) {
				parent->right = current;
			} else {
				parent->left = current;
			}
			InsertHelper(current);
			return;
		}
};

class Dict {
   
public: 
    RBTree* tree; 
    Dict();
	~Dict(); 

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);
    
    void dump_dictionary(string filename);

};
