#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
	Chaining() : bankStorage2d(capacity, std::vector<Account>()) {}
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    
    int capacity = 997;
    int n = 0;
    int m = capacity;
    double loadFactor = static_cast<double>(n)/m;
    std::vector<std::vector<Account>> bankStorage2d;
};

#endif // CHAINING_H
