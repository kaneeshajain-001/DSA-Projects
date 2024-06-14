/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
	type = "";
	id="";
    val = nullptr;
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
	type = t;
	UnlimitedInt* one = new UnlimitedInt("1");
	UnlimitedRational* frac = new UnlimitedRational(v,one);
	if (t=="VAL") {
		val = frac;
    	evaluated_value = frac; 
	} else {
		val = nullptr;
		evaluated_value = frac;
	}
	left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
	type = t;
	if (t=="VAL") {
		val = v;
    	evaluated_value = v; 
	} else {
		val = nullptr;
		evaluated_value = v;
	}
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode() {
	delete val; 
    delete evaluated_value; 
    delete left;
    delete right;
}
