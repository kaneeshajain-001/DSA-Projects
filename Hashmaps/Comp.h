#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
#include <cmath>

class Comp : public BaseClass {
public:
	Comp() : bankStorage1d(capacity, Account()){}
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int capacity = pow(2,17);
    std::vector<Account> bankStorage1d;
    int size = 0;
};


#endif // COMP_H
