/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"


bool compare(string i1, string i2) {
	if (i1.size() > i2.size()) {
		return true;
	} else if (i1.size() < i2.size()) {
		return false;
	} else if(i1==i2) {
		return true;
	} else {
		int i=0;
		while (i<i1.size()) {
			if (i1[i]>i2[i]) {
				return true;
			} else if (i1[i]<i2[i]) {
				return false;
			} else {
				i++;
			}
		}
	}
}

int countDigits(int i) {
	int num = 1;
	while ((i/10)!=0) {
		num++;
		i = i/10;
	}
	return num;
}

UnlimitedInt :: UnlimitedInt() {}

UnlimitedInt :: UnlimitedInt(string s) {
	if (s == "0") {
		unlimited_int = new int[1];
		unlimited_int[0] = 0;
		sign = 0;
		size = 1; 
	    capacity = 1;
	} else {
		if (s[0]=='-'){
			capacity = s.size()-1;
			sign = -1;
			size = s.size()-1;
		}else {
			capacity = s.size();
			sign = 1;
			size = s.size();
		}
		unlimited_int = new int[capacity];
		int j; 
		int i = 0;
		if (s[0]=='-'){
			j=1;
		} else {
			j=0;
		}
		int n = s.size();
		while (j < n) {
			unlimited_int[i] = s[j]-'0';
			j++;
			i++;
	    }
	}
}

UnlimitedInt :: UnlimitedInt(int i) {
	if (i == 0) {
		unlimited_int = new int[1];
		unlimited_int[0] = 0;
		sign = 0;
		size = 1;
		capacity = 1;
	} else {
		if (i>0) {
			sign = 1;
		} else {
			sign = -1;
			i = i*-1;
		}
		capacity = countDigits(i);
		size = countDigits(i);
		unlimited_int = new int[capacity];
		
		int j = capacity-1;
		while(j>=0) {
			unlimited_int[j] = i%10;
			i = i/10;
			j--;
		}
	}
} 

UnlimitedInt :: UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
	unlimited_int = ulimited_int;
	capacity = cap;
	size = sz;
	sign = sgn;
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt :: get_size(){
	return size;
}

int* UnlimitedInt :: get_array(){
	return unlimited_int;
}

int UnlimitedInt :: get_sign(){
	return sign;
}

int UnlimitedInt :: get_capacity() {
	return capacity;
}


string UnlimitedInt::to_string() {
    string result;
    if (sign == -1) {
        result += "-";
    }
    int i = 0;
    while (i < capacity - 1 && unlimited_int[i] == 0) {
        i++;
    }
    for (int j = i; j < capacity; j++) {
        result += std::to_string(unlimited_int[j]);
    }
    return result;
}

UnlimitedInt* UnlimitedInt :: add(UnlimitedInt* i1, UnlimitedInt* i2){
	
	string int1 = i1->to_string(); string int2 = i2->to_string();
	int size1 = int1.size(); int size2 = int2.size();
	int sign1 = i1->get_sign(); int sign2 = i2->get_sign();
	
	if(sign1==0){
		return i2;
	} 
	if(sign2==0) {
		return i1;
	}
	if (sign1 == sign2 and sign1==1){
        int size = max(size1, size2);
        int* temp = new int[size+1];
        int i = size1-1;
        int j = size2-1;
        int k = size;
        int carry = 0;
        while (k >= 0) {
            int num = carry;
            if (i >= 0)
                num += int1[i] - '0';
            if (j >= 0)
                num += int2[j] - '0';
            temp[k] = num % 10;
            carry = num / 10;
            i--;
            j--;
            k--;
        }
		temp[k] = carry;
		string s; int m;
		if (temp[0]==0) {
			m=1;
		} else {
			m=0;
		}
		for (m; m<size+1; m++) {
			s += std::to_string(temp[m]);
		}
		UnlimitedInt* i3 = new UnlimitedInt(s);
		return i3;
	} else if (sign1 == sign2 and sign1==-1) {
		int size = max(size1-1, size2-1);
        int* temp = new int[size+1];
        int i = size1-1;
        int j = size2-1;
        int k = size;
        int carry = 0;
        while (k >= 0) {
            int num = carry;
            if (i >= 1)
                num += int1[i] - '0';
            if (j >= 1)
                num += int2[j] - '0';
            temp[k] = num % 10;
            carry = num / 10;
            i--;
            j--;
            k--;
        }
		temp[k] = carry;
		string s = "-";
		int m;
		if (temp[0]==0) {
			m=1;
		} else {
			m=0;
		}
		for (m; m<size+1; m++) {
			s += std::to_string(temp[m]);
		}
		UnlimitedInt* i3 = new UnlimitedInt(s);
		return i3;
	} else if  (sign1 == -1 and sign2 == 1) {
		string s;
		int n1 = int1.size();
		for (int i=1; i<n1; i++){
			s += int1[i];
		}
		UnlimitedInt* i3 = new UnlimitedInt(s);
		return sub(i2,i3);
	} else if  (sign1 == 1 and sign2 == -1){
		string s;
		int n2 = int2.size();
		for (int i=1; i<n2; i++){
			s += int2[i];
		}
		UnlimitedInt* i3 = new UnlimitedInt(s);
		return sub(i1,i3);
	}
	return nullptr;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int size1= i1->get_size();
    int size2= i2->get_size();
    UnlimitedInt* minusOne = new UnlimitedInt("-1");
    if(i2->get_sign() == 0){
        return i1;
    }
    else if(i1->get_sign() == 0){
        UnlimitedInt* i4 = UnlimitedInt::mul(i2, minusOne);
        return i4;
    }
    else if(i1->to_string() == i2->to_string()){
        UnlimitedInt* zero = new UnlimitedInt("0");
        return zero;
    }
    else if(i1->get_sign() == 1 and i2->get_sign() == -1){
        UnlimitedInt* i4 = UnlimitedInt::mul(i2, minusOne);
        UnlimitedInt* ans = add(i1, i4);
        return ans;
    }
    else if(i1->get_sign() == -1 && i2->get_sign() == 1){
        UnlimitedInt* i3 = UnlimitedInt::mul(i2, minusOne);
        UnlimitedInt* ans= add(i1, i3);
        return ans;
    }
    else if(size1>size2) {
        int* temp = new int[size1];
        for(int i=0; i<size1; i++) {
            if(i<size1-size2){
                temp[i] = 0;
            }
            else{
                temp[i] = i2->unlimited_int[i+size2-size1];
            }
        }
        int borrow = 0;
        int* ans= new int[size1];
        for(int i=size1-1; i>=0; i--){
            int digit = ((i1->unlimited_int[i])-temp[i]+borrow);
            if(digit<0){
                ans[i]= digit+10;
                borrow=-1;
            }
            else{
                ans[i] = digit;
                borrow = 0;
            }
        }
        int sz=0;
        while(ans[sz] == 0){
            sz++;
        }
        string final;
        for(int i=sz; i<size1; i++){
            final += std::to_string(ans[i]);
        }
        UnlimitedInt* answer = new UnlimitedInt(final);
        answer->sign = (i1->sign);
        return answer;
    }
    else if(size1<size2){
        int* temp = new int[size2];
        for(int i=0; i<size2; i++){
            if(i<size2-size1){
                temp[i] = 0;
            }
            else{
                temp[i]= i1->unlimited_int[i+size1-size2];
            }
        }
        int borrow=0;
        int* ans= new int[size2];
        for(int i=size2-1; i>=0; i--){
            int digit= ((i2->unlimited_int[i])-temp[i]+borrow);
            if(digit<0){
                ans[i] = digit+10;
                borrow = -1;
            }
            else{
                ans[i] = digit;
                borrow = 0;
            }
        }
        int j = 0;
        while(ans[j] == 0){
            j++;
        }
        string final;
        for(int i=j; i<size2; i++){
            final += std::to_string(ans[i]);
        }
        UnlimitedInt* answer= new UnlimitedInt(final);
        answer->sign = (i1->sign)*-1;
        return answer;
    }
    else{
        if(compare(i1->to_string(),i2->to_string())){
            int* ans = new int[size1];
            int borrow = 0;
            for(int i=size1-1; i>=0; i--){
                int digit= ((i1->unlimited_int[i])- (i2->unlimited_int[i]) + borrow);
                if(digit<0){
                    ans[i]= digit+10;
                    borrow=-1;
                }
                else{
                    ans[i]= digit;
                    borrow= 0;
                }
            }
        int j=0;
        while(ans[j]==0){
            j++;
        }
        string final;
        for(int i=j; i<size2; i++){
            final += std::to_string(ans[i]);
        }
        UnlimitedInt* answer = new UnlimitedInt(final);
        answer->sign = i1->sign;
        return answer;
        }
        else{
            UnlimitedInt* ans = sub(i2, i1);
            ans->sign = (-1)*i1->sign;
            return ans;
        }
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* prod = new UnlimitedInt("0");
    if(i1->get_sign() == 0 || i2->get_sign() == 0){
        return prod;
    }
    
	UnlimitedInt* temp1= new UnlimitedInt(i1->to_string());
    UnlimitedInt* temp2= new UnlimitedInt(i2->to_string());
    
	for(int i=(i2->get_size()-1); i>=0; i--){
        UnlimitedInt* prim = new UnlimitedInt("0");
        for(int j=0; j<temp2->unlimited_int[i]; j++){
            prim = add(prim, temp1);
        }
        string s = prim->to_string();
        for(int k=0; k<i2->size-i-1; k++){
            s += "0";
        }
        prod = add(prod, new UnlimitedInt(s));
    }
    prod->sign= i1->sign*i2->sign;
    return prod;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
	UnlimitedInt* result = new UnlimitedInt("0");
	UnlimitedInt* minusOne = new UnlimitedInt("-1");
	UnlimitedInt* i3 = new UnlimitedInt();
	UnlimitedInt* i4 = new UnlimitedInt();
	if (i1->get_sign()==-1) {
		i3 = i3->mul(i1,minusOne);
	} else {
		i3 = i1;
	}
	
	if (i2->get_sign()==-1) {
		i4 = i4->mul(i2,minusOne);
	} else {
		i4 = i2;
	}
	
	int size1 = i3->get_size();
	int size2 = i4->get_size();
	
	if (size1<size2) {
		if ((i1->get_sign()==-1 and i2->get_sign()==1) or (i1->get_sign()==1 and i2->get_sign()==-1)) {
			return minusOne;
		}else {
			return result;
		}
	}
	int n  =size1-size2;
	UnlimitedInt* temp = new UnlimitedInt(i3->to_string());
	while (n>0) {
		string s1 = i4->to_string();
		string s2 = "1";
		for (int i=1; i<=n; i++) {
			s1 += "0";
			s2 += "0";                            
		}
		
		UnlimitedInt* first = new UnlimitedInt(s1);
		UnlimitedInt* second = new UnlimitedInt(s2);
		int i=0;
		while (temp->get_sign() != -1) {
			i++;
			temp = temp->sub(temp, first);
		}
		i = i-1;
		temp = temp->add(temp,first);
		if (i>0) {
			UnlimitedInt* fun = new UnlimitedInt(i);
			fun = fun->mul(fun, second);
			result = result->add(result,fun);
		}
		delete first; 
        delete second;
		n--;
	}
	int i = 0;
	while (temp->get_sign()!=-1) {
		temp = temp->sub(temp, i4); 
		i++;
	}
	i = i-1;
	temp = temp->add(temp,i4);
	UnlimitedInt* fun = new UnlimitedInt(i);
	result = result->add(result,fun);
	if ((i1->get_sign()==-1 and i2->get_sign()==1) or (i1->get_sign()==1 and i2->get_sign()==-1)) {
		result = result->mul(result,minusOne);
		if (temp->get_sign()!=0) {
			result = result->add(result,minusOne);
		}
	}
	
	return result;
}

	
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
	if ((i1->get_sign()==-1 and i2->get_sign()==-1) or (i1->get_sign()==1 and i2->get_sign()==1)) {
		UnlimitedInt* first = UnlimitedInt::div(i1,i2);
		UnlimitedInt* sec = UnlimitedInt::mul(i2,first);
		UnlimitedInt* result = UnlimitedInt::sub(i1,sec);
		return result;
	} else {
		UnlimitedInt* first = UnlimitedInt::div(i1,i2);
		UnlimitedInt* one = new UnlimitedInt("1");
		first = UnlimitedInt::add(first,one);
		UnlimitedInt* sec = UnlimitedInt::mul(i2,first);
		UnlimitedInt* result = UnlimitedInt::sub(i1,sec);
		return result;
	}
	return nullptr;
}

