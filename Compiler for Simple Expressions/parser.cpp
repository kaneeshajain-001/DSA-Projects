/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line

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

Parser::Parser(){
	symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression){
	if (expression[0] == "del") {
		ExprTreeNode* func = new ExprTreeNode();
		func->type = "DEL";
		func->id = "del";
		ExprTreeNode* equality = new ExprTreeNode();
		equality->type = "VAR";
		equality->id = ":=";
		ExprTreeNode* variable = new ExprTreeNode();
		variable->type = "VAR";
		variable->id = expression[2];
		equality->right = variable;
		equality->left = func;
		equality->right->num = symtable->search(expression[2]);
		expr_trees.push_back(equality);
	} else {
		ExprTreeNode* variable = new ExprTreeNode();
		if (expression[0] == "ret") {
			variable->type = "RET";
			variable->id = "ret";
		} else {
			variable->type = "VAR";
			variable->id = expression[0];
		}
		ExprTreeNode* equality = new ExprTreeNode();
		equality->type = "VAR";
		equality->id = ":=";
		equality->left = variable;
		int i = 2;
		int n = expression.size();
		StackS op;
		StackT operand;
		while (i<n) {
			if (expression[i]=="(") {
				op.push("(");
				i++;
			} else if (expression[i]=="+" or expression[i]=="-" or expression[i]=="*" or expression[i]=="/") {
				op.push(expression[i]);
				i++;
			} else if (expression[i][0] == '-' || isdigit(expression[i][0])){
				int p = stoi(expression[i]);
				ExprTreeNode* value = new ExprTreeNode("VAL", p);
				operand.push(value);
				i++;
			} else if (expression[i]==")") {
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
				variable->id = expression[i];
				operand.push(variable);
				i++;
			}
		}
		ExprTreeNode* connect = operand.pop();
		equality->right = connect;
		expr_trees.push_back(equality);
		if (variable->type == "VAR") {
			symtable->insert(variable->id);
		}
	}
	return;
}

Parser::~Parser(){
	delete symtable;
}
