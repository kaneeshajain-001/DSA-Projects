// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class Sentence{
public:
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    string s;
    // this will form the elements of the vector

    Sentence(){
    }
    ~Sentence(){
    }
};

class SearchEngine {
private:
    // You can add attributes/helper functions here

public: 
    vector<Sentence> sentences; // this will store all the sentences entered one by one
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};