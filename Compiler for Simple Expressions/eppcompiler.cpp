/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler() {
	memory_size = 0;
    output_file = "";
    ofstream file(output_file);
    file.close();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
	output_file = out_file;
	memory_size = mem_limit;
	for (int i=0; i<memory_size; i++) {
		mem_loc.push_back(i);
	}
	ofstream file(output_file);
    file.close();
}

void EPPCompiler::compile(vector<vector<string>> code){
	for (int i=0; i<code.size(); i++) {
		if (code[i][0] == "del") {
			int memory = targ.symtable->search(code[i][2]);
			mem_loc.push_back(memory);
			targ.symtable->remove(code[i][2]);
		} 
		if (code[i][0] != "ret" and  code[i][0] != "del") {
			if (targ.symtable->search(code[i][0]) == -2 || targ.symtable->search(code[i][0]) == -1) {
				targ.symtable->insert(code[i][0]);
				targ.symtable->assign_address(code[i][0], mem_loc.back());
				mem_loc.pop_back();
			}
		}
		targ.parse(code[i]);
		int n = targ.expr_trees.size();
		ExprTreeNode* root = targ.expr_trees[n-1];
		write_to_file(generate_targ_commands());
	}
}

void generateHelper(SymbolTable* SymTable, ExprTreeNode* node, vector<string>& result) {
	if (!node) {
		return;
	}
	
	if (node->left == nullptr and node->right == nullptr) {
		if (node->type == "VAL") {
			result.push_back("PUSH " + std::to_string(node->num));
			return;
		}else if (node->type == "VAR") {
			int i = SymTable->search(node->id);
			result.push_back("PUSH mem[" + std::to_string(i) + "]");
			return;
		}
	}
	
	generateHelper(SymTable, node->right, result);
	generateHelper(SymTable, node->left, result);
	
	if (node->type == "ADD") {
		result.push_back("ADD");
	} else if (node->type == "SUB") {
		result.push_back("SUB");
	} else if (node->type == "MUL") {
		result.push_back("MUL");
	} else if (node->type == "DIV") {
		result.push_back("DIV");
	}
}

vector<string> EPPCompiler::generate_targ_commands(){
	vector<string> final;
	int n = targ.expr_trees.size();
	ExprTreeNode* root = targ.expr_trees[n-1];
	
	if (root->left->type == "VAR") {
		generateHelper(targ.symtable, root->right, final);
		int a = targ.symtable->search(root->left->id);
		string s = "mem[" + std::to_string(a) + "] = POP";
		final.push_back(s);
		return final;
	} else if (root->left->type == "DEL") {
		int a = targ.symtable->search(root->right->id);
		string s = "DEL = mem[" + to_string(a) + "]";
		targ.symtable->remove(root->right->id);
        final.push_back(s);
        return final;
	} else {
		generateHelper(targ.symtable, root->right, final);
		final.push_back("RET = POP");
		return final;
	}
}

void EPPCompiler::write_to_file(vector<string> commands) {
    string ans;
    for (string s : commands) {
    	ans += s + "\n";
	}
	fstream file(output_file, ios::app);
	file<<ans<<endl;
	file.clear();
}


EPPCompiler::~EPPCompiler(){
	
}
