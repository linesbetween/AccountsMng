#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include "UserClass.h"
#include "Transaction.h"
using namespace std;

static vector<User> userList; 
static vector<Transaction> transList;

int main(){

	fstream oldMaster("old master.txt", ios::in);
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

	fstream transaction("transaction.txt", ios::in);

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


	// apply transation   (and display result) (and write to file)   //////////////////
	cout << "\n\n  Transaction Result: \n";
	cout << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;

	fstream result("New Master.txt", ios::out);
	result << left << fixed << setprecision(2);
	result << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;

	bool found = false;
	for (Transaction trans : transList){
		found = false;
		for (User user : userList){
			if (trans.getAccount() == user.getAccount()){
				user.setBalance(user.getBalance() + trans.getAmount());
				found = true;
			    user.print();
				result << setw(16) << user.getAccount() << setw(24) << user.getName() << setw(16) << user.getBalance() << endl;
			}
		}

		if (found == false){
			cout << "Unmatched transaction record for account " << trans.getAccount() << endl;
		}

	}

	// display new master   //////////////
	/*
	cout << "\n\n  New Master; \n";
	cout << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;
	for (User user : userList){
		user.print();
	}
	cout << endl << endl;
	*/


	/// write result to result file   /////////////////
	/*
	fstream result("New Master.txt", ios::out);
	result << left << fixed << setprecision(2);
	result << setw(16) << "ACCT Number" << setw(24) << "NAME" << setw(16) << "BALANCE" << endl;
	for (User user : userList){
		result << setw(16) << user.getAccount() << setw(24) << user.getName() << setw(16) << user.getBalance() << endl;
	}
	*/
	_getch();
	return 0;
}