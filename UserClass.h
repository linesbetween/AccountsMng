#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

 class User {

 private:
	 string accountNum;
	 string name;
	 double balance;

 public:

	 User(){
		 accountNum = "default";
		 name = "default";
		 balance = 0;
	 }

	 User(string  acc, string n, double ba){
		 accountNum = acc;
		 name = n;
		 balance = ba;
	 }


	 string getAccount(){ return accountNum; }
	 string getName(){ return name; }
	 double getBalance(){ return balance; }

	 void setBalance(double ba){ balance = ba; }
	 
	 void print(){
		 cout << setw(16) << accountNum << setw(24) << name << setw(16) << balance <<endl;
	 }

};

#endif