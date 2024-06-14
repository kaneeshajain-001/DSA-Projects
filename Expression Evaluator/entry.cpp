/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
	key="";
	val= NULL;
	left=NULL;
	right=NULL;
	
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
	this->key=k;
	this->val =v;
	this->left = NULL; 
	this->right = NULL;
}

SymEntry::~SymEntry(){
    delete left;
    delete right;
	delete val;
    
	key="";
}
