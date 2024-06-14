/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

bool compare2(string i1, string i2) {
	int s1 = i1.size();
	int s2 = i2.size();
	if (s1 > s2) {
		return true;
	} else if (s1 < s2) {
		return false;
	} else if(s1 == s2) {
		return true;
	} else {
		int i=0;
		while (i<s1) {
			if (i1[i]>i2[i]) {
				return true;
			} else if (i1[i]<i2[i]) {
				return false;
			} else {
				i++;
			}
		}
	}
	return false;
}

UnlimitedRational :: UnlimitedRational(){}

UnlimitedRational :: UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
	if (den->to_string()=="0") {
		p = new UnlimitedInt("0");
		q = new UnlimitedInt("0");
	} else if (num->to_string()=="0"){
		p = new UnlimitedInt("0");
		q = new UnlimitedInt("1");
	} else if (num->to_string() == den->to_string()) {
		p = new UnlimitedInt("1");
		q = new UnlimitedInt("1");
	} else if ((UnlimitedInt::mod(num,den))->get_sign() == 0) {
		p = UnlimitedInt::div(num,den);
		q = new UnlimitedInt("1");
	} else if ((UnlimitedInt::mod(den,num))->get_sign() == 0) {
		p = new UnlimitedInt("1");
		q = UnlimitedInt::div(den,num);
	} else {
		UnlimitedInt* minusOne = new UnlimitedInt("-1");
		UnlimitedInt* numF = new UnlimitedInt();
		UnlimitedInt* denF = new UnlimitedInt();
		if (num->get_sign() == -1) {
			numF = UnlimitedInt::mul(num, minusOne);
		} else {
			numF = num;
		}
		if (den->get_sign() == -1) {
			denF = UnlimitedInt::mul(den, minusOne);
		} else {
			denF = den;
		}
		
		string s1 = numF->to_string();
		string s2 = denF->to_string();
		if (compare2(s1,s2)) {
			UnlimitedInt* temp = new UnlimitedInt(denF->to_string());
			UnlimitedInt* remainder =  UnlimitedInt::mod(numF,denF);
		    UnlimitedInt* quotient = temp;
			while(remainder->get_sign() != 0) {
				temp = quotient;
				quotient = remainder;
				remainder = UnlimitedInt::mod(temp,quotient);
			}
			p = UnlimitedInt::div(numF,quotient);
			if ((num->get_sign()==-1 and den->get_sign()==1) or (num->get_sign()==1 and den->get_sign()==-1)) {
				p = UnlimitedInt::mul(p,minusOne);
			}
			q = UnlimitedInt::div(denF,quotient);
			
		} else {
			UnlimitedInt* temp = new UnlimitedInt(numF->to_string());
			UnlimitedInt* remainder =  UnlimitedInt::mod(denF,numF);
			UnlimitedInt* quotient = numF;
			while(remainder->get_sign() != 0) {
				temp = quotient;
				quotient = remainder;
				remainder = UnlimitedInt::mod(temp,quotient);
			}
			p = UnlimitedInt::div(numF,quotient);
			if ((num->get_sign()==-1 and den->get_sign()==1) or (num->get_sign()==1 and den->get_sign()==-1)) {
				p = UnlimitedInt::mul(p,minusOne);
			}
			q = UnlimitedInt::div(denF,quotient);
		}
	}
} 

UnlimitedRational :: ~UnlimitedRational() {
	delete p;
	delete q;
}
		
UnlimitedInt* UnlimitedRational :: get_p() {
	return p;
}

UnlimitedInt* UnlimitedRational :: get_q() {
	return q;
}

string  UnlimitedRational :: get_p_str() {
	return p->to_string();
}

string  UnlimitedRational :: get_q_str() {
	return q->to_string();
}

string UnlimitedRational :: get_frac_str() {
	string s = p->to_string();
	s += "/";
	s += q->to_string();
	return s;
}

UnlimitedRational* UnlimitedRational :: add(UnlimitedRational* i1, UnlimitedRational* i2) {
	UnlimitedInt* p1 = i1->get_p();
	UnlimitedInt* p2 = i2->get_p();
	UnlimitedInt* q1 = i1->get_q();
	UnlimitedInt* q2 = i2->get_q();
	UnlimitedInt* num = new UnlimitedInt("0");
	UnlimitedInt* den = new UnlimitedInt("0");
	num = UnlimitedInt::add(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(q1,p2));
	den = UnlimitedInt::mul(q1,q2);
	UnlimitedRational* result = new UnlimitedRational(num,den);
	return result;
}

UnlimitedRational* UnlimitedRational :: sub(UnlimitedRational* i1, UnlimitedRational* i2) {
	UnlimitedInt* p1 = i1->get_p();
	UnlimitedInt* p2 = i2->get_p();
	UnlimitedInt* q1 = i1->get_q();
	UnlimitedInt* q2 = i2->get_q();
	UnlimitedInt* num = new UnlimitedInt("0");
	UnlimitedInt* den = new UnlimitedInt("0");
	num = UnlimitedInt::sub(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(q1,p2));
	den = UnlimitedInt::mul(q1,q2);
	UnlimitedRational* result = new UnlimitedRational(num,den);
	return result;
}

UnlimitedRational* UnlimitedRational :: mul(UnlimitedRational* i1, UnlimitedRational* i2) {
	UnlimitedInt* p1 = i1->get_p();
	UnlimitedInt* p2 = i2->get_p();
	UnlimitedInt* q1 = i1->get_q();
	UnlimitedInt* q2 = i2->get_q();
	UnlimitedInt* num = UnlimitedInt::mul(p1,p2);
	UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
	UnlimitedRational* result = new UnlimitedRational(num,den);
	return result;
}

UnlimitedRational* UnlimitedRational :: div(UnlimitedRational* i1, UnlimitedRational* i2){
	UnlimitedInt* p1 = i1->get_p();
	UnlimitedInt* p2 = i2->get_p();
	UnlimitedInt* q1 = i1->get_q();
	UnlimitedInt* q2 = i2->get_q();
	UnlimitedInt* num = UnlimitedInt::mul(p1,q2);
	UnlimitedInt* den = UnlimitedInt::mul(q1,p2);
	UnlimitedRational* result = new UnlimitedRational(num,den);
	return result;
}



