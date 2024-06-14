#include "Chaining.h"
using namespace std;

vector<int> merge1(vector<int> left, vector<int> right) {
    vector<int> result = {};
    int i = 0, j = 0;
    while (i<left.size() && j<right.size()) {
        if (left[i]<right[j]) {
            result.push_back(left[i]);
            i += 1;
        } else {
            result.push_back(right[j]);
            j += 1;
        }
    }
    while (i<left.size()) {
        result.push_back(left[i]);
        i += 1;
    }
    while (j<right.size()) {
        result.push_back(right[j]);
        j += 1;
    }
    return result;
}

vector<int> merge_sort1(vector<int> vec) {
    if (vec.size() < 2) {
        return vec;
    } else {
        vector<int> left, right;
        int middle = vec.size()/2;
        for (int i=0; i<middle; i++) {
            left.push_back(vec[i]);
        }
        for (int i=middle; i<vec.size(); i++) {
            right.push_back(vec[i]);
        }
        return merge1(merge_sort1(left), merge_sort1(right));
    }
}

void Chaining::createAccount(string id, int count) {
    n += 1;
    loadFactor = static_cast<double>(n)/m;
    if (loadFactor > 0.7) {
    	capacity = capacity*2;
    	vector<vector<Account>> Data(capacity);
    	for (int i=0; i<bankStorage2d.size(); i++){
    		vector<Account> vec = bankStorage2d[i];
    		for (int j=0; j<vec.size(); j++) {
    			Account a = vec[j];
    			int hashKey2 = hash(a.id);
    			Data[hashKey2].push_back(a);
			}
		}
		bankStorage2d.clear();
		bankStorage2d = Data;
		m = capacity;
	}
	int hashKey = hash(id);
	Account a1 = {id, count};
	bankStorage2d[hashKey].push_back(a1);
}

vector<int> Chaining::getTopK(int k) {
	vector<int> values;
    vector<int> result;
    for (int i=0; i<bankStorage2d.size(); i++){
    	if (!(bankStorage2d[i].empty())){
    		for (int j=0; j<bankStorage2d[i].size(); j++){
    			values.push_back(bankStorage2d[i][j].balance);
			}
		}
	}
	values = merge_sort1(values);
	int num = values.size();
	if(num>k) {
		for (int i = num-1; i>num-k-1; i--){
			result.push_back(values[i]);
		}
	} else {
		for (int i = num-1; i>=0; i--){
			result.push_back(values[i]);
		}
	}
	return result;	
}

int Chaining::getBalance(string id) {
    if (!(doesExist(id))){
    	return -1;
	} else {
		int hashKey = hash(id);
		vector<Account> vec = bankStorage2d[hashKey];
		for (int i=0; i<vec.size(); i++) {
			Account a1 = vec[i];
			if (a1.id == id) {
				return a1.balance;
			}
		}
	}
	return -1;
}

void Chaining::addTransaction(string id, int count) {
    if (!(doesExist(id))){
    	createAccount(id, count);
	} else {
		int hashKey = hash(id);
		vector<Account> &vec = bankStorage2d[hashKey];
		for (int i=0; i<vec.size(); i++) {
			Account &a1 = vec[i];
			if (a1.id == id) {
				a1.balance += count;
				break;
			}
		}
	}
}

bool Chaining::doesExist(string id) {
    int hashKey = hash(id);
    if (bankStorage2d[hashKey].empty()){
    	return false;
	} else {
		vector<Account> vec = bankStorage2d[hashKey];
		for (int i=0; i<vec.size(); i++) {
			Account a1 = vec[i];
			if (a1.id == id) {
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Chaining::deleteAccount(string id) {
    if (!(doesExist(id))){
    	return false;
	} else {
		loadFactor = static_cast<double>(n)/m;
		int hashKey = hash(id);
		vector<Account> &vec = bankStorage2d[hashKey];
		for (auto it = vec.begin(); it != vec.end(); ++it) {
		    Account &a1 = *it;
		    if (a1.id == id) {
		        vec.erase(it);
		        break;
		    }
		}
		
		n -= 1;
		loadFactor = static_cast<double>(n)/m;
		
	    if (loadFactor < 0.7) {
	    	capacity = capacity/2;
	    	vector<vector<Account>> Data(capacity, vector<Account>());
	    	for (int i=0; i<bankStorage2d.size(); i++){
	    		vector<Account> vec = bankStorage2d[i];
	    		for (int j=0; j<vec.size(); j++) {
	    			Account a = vec[j];
	    			int hashKey2 = hash(a.id);
	    			Data[hashKey2].push_back(a);
				}
			}
			bankStorage2d.clear();
			bankStorage2d = Data;
			m = capacity;
		}
		return true;
	}
	return false;
}

int Chaining::databaseSize() {
    return n;
}

int Chaining::hash(string id) {
    
	int sum = 0;
	for (int i=0; i<id.size(); i++){
		char c = id[i];
		sum += static_cast<int>(c)*i;
	}
	return sum % capacity;
}

