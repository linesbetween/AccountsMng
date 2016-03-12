#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Transaction {

private:
	string account;
	double amount;

public:

	Transaction(){
		account = "default";
		amount = 0;
	}

	Transaction(string  acc, double am){
		account = acc;
		amount = am;
	}


	string getAccount(){ return account; }
	double getAmount(){ return amount; }

	void setAmount(double am){ amount = am; }

	void print(){
		cout << setw(16) << account<< setw(16) << amount << endl;
	}

};

#endif