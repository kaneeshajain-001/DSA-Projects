#include "CubicProbing.h"
using namespace std;

vector<int> merge3(vector<int> left, vector<int> right) {
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

vector<int> merge_sort3(vector<int> vec) {
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
        return merge3(merge_sort3(left), merge_sort3(right));
    }
}

bool occupied2(struct Account a){
	if (a.id.empty() || a.id == "#") {
		return false;
	}
	return true;
}

void CubicProbing::createAccount(string id, int count) {
	int hashKey = hash(id);
	Account a1 = {id, count};
	int index = hashKey;
	long long int i = 1;
	bool lp = false;
	while (occupied2(bankStorage1d[index])){
		index = (index+i*i*i)%capacity;
		i++;
		if (i>capacity) {
			lp = true;
			break;
		}
	}
	if (lp) {
		while (occupied2(bankStorage1d[index])) {
			index = (index+1)/capacity;
		}
	}
	bankStorage1d[index] = a1;
	size++;
}

vector<int> CubicProbing::getTopK(int k) {
	vector<int> values;
    vector<int> result;
    
    for (int i=0; i<bankStorage1d.size(); i++){
    	if (occupied2(bankStorage1d[i])) {
    		values.push_back(bankStorage1d[i].balance);
		}
	}
	values = merge_sort3(values);
	int num = values.size();
	if (num > k) {
		for (int i = num-1; i>num-k-1; i--){
			result.push_back(values[i]);
		}
	}else {
		for (int i = num-1; i>=0; i--){
			result.push_back(values[i]);
		}
	}
	return result;
}

int CubicProbing::getBalance(string id) {
    if (doesExist(id)){
    	int index = hash(id);
    	long long int i = 1;
    	bool lp = false;
    	while(bankStorage1d[index].id!=id){
    		index = (index+i*i*i)%capacity;
    		i++;
    		if (i >= capacity) {
    			lp = true;
    			break;
			}
		}
		if (lp) {
			while(bankStorage1d[index].id!=id){
    			index = (index+1)%capacity;
    			i++;
			}
		}
		return bankStorage1d[index].balance;
	} else {
		return -1;
	}
}

void CubicProbing::addTransaction(string id, int count) {
    if (doesExist(id)){
    	int index = hash(id);
    	long long int i = 1;
    	bool lp = false;
    	while(bankStorage1d[index].id!=id){
    		index = (index+i*i*i)%capacity;
    		i++;
    		if (i >= capacity) {
    			lp = true;
    			break;
			}
		}
		if (lp) {
			while(bankStorage1d[index].id!=id){
    			index = (index+1)%capacity;
    			i++;
			}
		}
		Account &a1 = bankStorage1d[index];
		a1.balance += count;
	} else {
		createAccount(id, count);
	}
}

bool CubicProbing::doesExist(string id) {
    int index = hash(id);
    long long int i = 1;
	bool notFound = true, lp = false;
	while (notFound) {
		if (bankStorage1d[index].id == id && occupied2(bankStorage1d[index])) {
			return true;
		}
		if (bankStorage1d[index].id.empty()){
			return false;
		}
		index = (index + i*i*i) % capacity;
        i += 1;
        if (i >= capacity) {
        	lp = true;
        	break;
		}
	}
	if (lp) {
		int originalIndex = index;
		while (index != originalIndex) {
	        if (bankStorage1d[index].id == id && occupied2(bankStorage1d[index])) {
	            return true;
	        }
	        if (bankStorage1d[index].id.empty()) {
	        	return false;
			}
	        index = (index + 1) % capacity;
	        i += 1;
	    }
	}
	return false;
}

bool CubicProbing::deleteAccount(string id) {
    if (doesExist(id)){
    	int index = hash(id);
    	long long int i = 1;
    	bool lp = false;
    	while(bankStorage1d[index].id!=id){
    		index = (index+i*i*i)%capacity;
    		i++;
    		if (i >= capacity) {
    			lp = true;
    			break;
			}
		}
		if (lp) {
			while(bankStorage1d[index].id!=id){
    			index = (index+1)%capacity;
    			i++;
			}
		}
		Account &a1 = bankStorage1d[index];
		a1.id = "#";
		size--;
		return true;
	} else {
		return false;
	}
	return false;
}


int CubicProbing::databaseSize() {
	return size;
}

int CubicProbing::hash(string id) {
    
	int sum = 0;
	for (int i=0; i<id.size(); i++){
		char c = id[i];
		sum += static_cast<int>(c)*i;
	}
	return sum % capacity;
}

