//Read user data form Old Master.txt and display
//Read transactions from Transaction.txt and display
//Apply transactiont to old master, create new master and write result to it.
//AccountsMngMain.cpp
//Hanfei Xu CIT284
//Mar 12 2016


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctype.h>
#include "UserClass.h"
#include "Transaction.h"
using namespace std;

static vector<User> userList; 
static vector<Transaction> transList;

int main(){

	fstream oldMaster("Old Master.txt", ios::in);
	string account, name , balanceStr, titleAccount, titleName, titleBalanceStr;
	string amountStr, titleAmountStr;
	double balance;


	// load old master   /////////////////

	if (oldMaster){
		cout << "  Old Master \n";

		getline(oldMaster, titleAccount, '%');
		getline(oldMaster, titleName, '%');
		getline(oldMaster, titleBalanceStr, '%');
		oldMaster.ignore(1000, '\n');


		while (!oldMaster.eof()){
			getline(oldMaster, account, '%');
			getline(oldMaster, name, '%');
			getline(oldMaster, balanceStr, '%');
			oldMaster.ignore(1000, '\n');

			userList.emplace_back(account, name, stod(balanceStr));
		}
		
	}

	oldMaster.close();
	// display old master
	cout << left <<fixed <<setprecision(2);
	cout << setw(16) << titleAccount << setw(24) << titleName << setw(16) << titleBalanceStr <<endl;
	for (User user : userList){
		user.print();
	}
	cout << endl << endl;

	// load transation    ///////////////////

	fstream transaction("Transaction.txt", ios::in);

	if (transaction){
		cout << "  Transaction \n";

		getline(transaction, titleAccount, '%');
		getline(transaction, titleAmountStr, '%');
		transaction.ignore(1000, '\n');


		while (!transaction.eof()){
			getline(transaction, account, '%');
			getline(transaction, amountStr, '%');
			transaction.ignore(1000, '\n');

			transList.emplace_back(account, stod(amountStr));
		}

	}

	transaction.close();
	// display transaction 
	cout << setw(16) << titleAccount << setw(16) << titleAmountStr << endl;
	for (Transaction transaction : transList){
		transaction.print();
	}


	// apply transation   (and display result)   //////////////////
	cout << "\n\n  Transaction Result: \n";
	cout << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;

	//fstream result("New Master.txt", ios::out);
	//result << left << fixed << setprecision(2);
	//result << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;

	bool found = false;
	for (Transaction trans : transList){
		found = false;
		auto it = userList.begin();
		for (int i = 0; it < userList.end(); ++it, ++i){
			if (trans.getAccount() == it->getAccount()){
				it->setBalance(it->getBalance() + trans.getAmount());
				found = true;
			    it->print();
				//result << setw(16) << it->getAccount() << setw(24) << it->getName() << setw(16) << it->getBalance() << endl;
			}
		}

		if (found == false){
			cout << "Unmatched transaction record for account " << trans.getAccount() << endl;
		}

	}

	// display new master   //////////////
	
	cout << "\n\n  New Master; \n";
	cout << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;
	for (User user : userList){
		user.print();
	}
	cout << endl << endl;
	


	/// write result to new master file   /////////////////
	
	fstream result("New Master.txt", ios::out);
	result << left << fixed << setprecision(2);
	result << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;
	for (User user : userList){
		result << setw(16) << user.getAccount() << setw(24) << user.getName() << setw(16) << user.getBalance() << endl;
	}
	
	_getch();
	return 0;
}