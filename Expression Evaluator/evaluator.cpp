/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

class StackT {
private:
    vector<ExprTreeNode*> stack;

public:
    StackT() {}

    void push(ExprTreeNode* data) {
        stack.push_back(data);
    }

    ExprTreeNode* pop() {
        int n = stack.size();
        ExprTreeNode* a = stack[n - 1];
        stack.pop_back();
        return a;
    }
    int get_size() {
    	int n = stack.size();
    	return n;
	}
};

class StackS {
private:
    vector<string> stack;

public:
    StackS() {}

    void push(string data) {
        stack.push_back(data);
    }

    string pop() {
        int n = stack.size();
        string a = stack[n - 1];
        stack.pop_back();
        return a;
    }
    int get_size() {
    	int n = stack.size();
    	return n;
	}
};

Evaluator::Evaluator() {
	symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
	delete symtable;
}

void Evaluator::parse(vector<string> code) {
	ExprTreeNode* variable = new ExprTreeNode();
	variable->type = "VAR";
	variable->id = code[0];
	ExprTreeNode* equality = new ExprTreeNode();
	equality->type = "VAR";
	equality->id = ":=";
	equality->left = variable;
	int i = 2;
	int n = code.size();
	StackS op;
	StackT operand;
	while (i<n) {
		if (code[i]=="(") {
			op.push("(");
			i++;
		} else if (code[i]=="+" or code[i]=="-" or code[i]=="*" or code[i]=="/") {
			op.push(code[i]);
			i++;
		} else if (code[i][0] == '-' || isdigit(code[i][0])){
			UnlimitedInt* p = new UnlimitedInt(code[i]);
			ExprTreeNode* value = new ExprTreeNode("VAL", p);
			operand.push(value);
			i++;
		} else if (code[i]==")") {
			string s = op.pop();
			ExprTreeNode* x = new ExprTreeNode();
			if (s=="+") {
				x->type = "ADD";
			} else if (s=="-") {
				x->type = "SUB";
			} else if (s=="*") {
				x->type = "MUL";
			} else if (s=="/") {
				x->type = "DIV";
			}
			x->right = operand.pop();
			x->left = operand.pop();
			op.pop();
			operand.push(x);
			i++;
		} else {
			ExprTreeNode* variable = new ExprTreeNode();
			variable->type = "VAR";
			variable->id = code[i];
			operand.push(variable);
			i++;
		}
	}
	ExprTreeNode* connect = operand.pop();
	equality->right = connect;
	expr_trees.push_back(equality);
}

UnlimitedRational* solve(ExprTreeNode* root, SymbolTable* symtable) {
    if (root == nullptr)
        return nullptr;

    if (root->evaluated_value != nullptr) {
        return root->evaluated_value;
    }

    if (root->type == "VAR") {
        string k = root->id;
        root->evaluated_value = symtable->search(k);
    } 
    
    UnlimitedRational* value1 = solve(root->left, symtable);
    UnlimitedRational* value2 = solve(root->right, symtable);

    string s = root->type;
    if (s == "ADD") {
        root->evaluated_value = UnlimitedRational::add(value1, value2);
    } else if (s == "SUB") {
        root->evaluated_value = UnlimitedRational::sub(value1, value2);
    } else if (s == "MUL") {
        root->evaluated_value = UnlimitedRational::mul(value1, value2);
    } else if (s == "DIV") {
        root->evaluated_value = UnlimitedRational::div(value1, value2);
    }
    

    return root->evaluated_value;
}

void Evaluator::eval() {
    ExprTreeNode* equality = expr_trees.back();
    UnlimitedRational* Right = solve(equality->right, symtable);
    string key = equality->left->id;
    symtable->insert(key, Right);
}
