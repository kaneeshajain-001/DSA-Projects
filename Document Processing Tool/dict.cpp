// Do NOT add any other includes
#include "dict.h"
int compare2(string s1, string s2) {
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

bool is_separator2(char c) {
    if (c == ' ' || c == '.' || c == ',' || c == '-' || c == ':' || c == '!' || c == '"'|| c == '(' || c == ')' || c == '?' || c == '[' || c == ']' 
	|| c == 39|| c == 145|| c == 146|| c == 147|| c == 148|| c == 183|| c == ';' || c == '@') {
        return true;
    }
    return false;
}

vector<string> split_sentence2(string sentence) {
	int i = 0;
	vector<string> result;
	string s;
	while (i<sentence.size()) {
		if (is_separator2(sentence[i])) {
			if (s.size()!=0) {
				result.push_back(s);
				s = "";
			}
			i++;
		} else {
			s += sentence[i];
			i++;
		}
	}
	if (!(is_separator2(sentence[i-1]))) {
		result.push_back(s);
	}
	return result;
}

Dict::Dict() {
	tree = new RBTree();
}

void drastic(node* root) {
    if (root) {
        drastic(root->left);
        drastic(root->right);
        delete root;
    }
}

Dict::~Dict() {
    drastic(tree->root); 
    delete tree; 
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<string> ans = split_sentence2(sentence);
    for (string s : ans) {
        node* newNode = new node(s, 'r');
        if (tree->root) {
            node* current = tree->root;
            bool found = false;
            int comparisonResult = 0;
            while (current) {
                comparisonResult = compare2(newNode->word, current->word);
                if (comparisonResult == 0) {
                    current->count += 1;
                    found = true;
                    break;
                } else if (comparisonResult == 1) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
            if (!found) {
                tree->insert(newNode);
            }
        } else {
            tree->root = newNode;
            tree->root->color = 'b';
            tree->root->count = 1;
        }
    }
    return;
}

int Dict::get_word_count(string word){
    node* current = tree->root;
	while (current) {
		if (compare2(word, current->word) == 0) {
			return current->count;
		} else if (compare2(word, current->word) == 1) {
			current = current->right;
		} else {
			current = current->left;
		}
	}
    return -1;
}

void inorder(node* root, string& filename) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, filename);
    fstream file(filename, ios::app);
    string input = root->word;
    for (char &c : input) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    }
    file << input << ", " << root->count << "\n";
    file.close();
    inorder(root->right, filename);
}

void Dict::dump_dictionary(string filename) {
	
    std::ofstream file(filename);
    file.close();
    inorder(tree->root, filename);
    
}
// Do NOT add any other includes
#include "dict.h"
int compare2(string s1, string s2) {
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

bool is_separator2(char c) {
    if (c == ' ' || c == '.' || c == ',' || c == '-' || c == ':' || c == '!' || c == '"'|| c == '(' || c == ')' || c == '?' || c == '[' || c == ']' 
	|| c == 39|| c == 145|| c == 146|| c == 147|| c == 148|| c == 183|| c == ';' || c == '@') {
        return true;
    }
    return false;
}

vector<string> split_sentence2(string sentence) {
	int i = 0;
	vector<string> result;
	string s;
	while (i<sentence.size()) {
		if (is_separator2(sentence[i])) {
			if (s.size()!=0) {
				result.push_back(s);
				s = "";
			}
			i++;
		} else {
			s += sentence[i];
			i++;
		}
	}
	if (!(is_separator2(sentence[i-1]))) {
		result.push_back(s);
	}
	return result;
}

Dict::Dict() {
	tree = new RBTree();
}

void drastic(node* root) {
    if (root) {
        drastic(root->left);
        drastic(root->right);
        delete root;
    }
}

Dict::~Dict() {
    drastic(tree->root); 
    delete tree; 
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<string> ans = split_sentence2(sentence);
    for (string s : ans) {
        node* newNode = new node(s, 'r');
        if (tree->root) {
            node* current = tree->root;
            bool found = false;
            int comparisonResult = 0;
            while (current) {
                comparisonResult = compare2(newNode->word, current->word);
                if (comparisonResult == 0) {
                    current->count += 1;
                    found = true;
                    break;
                } else if (comparisonResult == 1) {
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
            if (!found) {
                tree->insert(newNode);
            }
        } else {
            tree->root = newNode;
            tree->root->color = 'b';
            tree->root->count = 1;
        }
    }
    return;
}

int Dict::get_word_count(string word){
    node* current = tree->root;
	while (current) {
		if (compare2(word, current->word) == 0) {
			return current->count;
		} else if (compare2(word, current->word) == 1) {
			current = current->right;
		} else {
			current = current->left;
		}
	}
    return -1;
}

void inorder(node* root, string& filename) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, filename);
    fstream file(filename, ios::app);
    string input = root->word;
    for (char &c : input) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    }
    file << input << ", " << root->count << "\n";
    file.close();
    inorder(root->right, filename);
}

void Dict::dump_dictionary(string filename) {
	
    std::ofstream file(filename);
    file.close();
    inorder(tree->root, filename);
    
}
