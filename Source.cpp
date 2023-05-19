#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<ctime>
#include<chrono>
#include"Header.h"

using namespace std;
vector<Customer> cus;
vector<Admin> ad;

float Customer::withdrawal(float out) {
	float n = cb - out;
	cb = n;
	if (!transactions.size()) {
		if (n >= 0) {
			printf("Transaction successfully. Your current balance: $%.3f\n", cb);
		}
		else {
			std::cout << "You have a negative balance and you will have to pay interest" << endl;
			message.push_back("You have a debt of " + to_string(-cb));
		}
	}
	else {
		std::cout << "You have a negative balance and you will have to pay interest" << endl;
		message.push_back("You have a debt of " + to_string(-cb));
	}
	message.push_back(to_string(out) + 'W');
	transactions.push_back(cb);
	return cb;
}

float Customer::deposit(float d) {
	float n = cb + d;
	cb = n;
	message.push_back(to_string(d) + 'D');
	transactions.push_back(cb);
	printf("You have deposited $%.3f. Your current balance is $%.3f. ", d, cb);
	return cb;
}

float Customer::transfer(float m, int cid) {
	Customer to_cid;
	bool check = false;
	for (auto& to_cid : cus) {
		if (to_cid.getCID() == cid) {
			check = true;
		}
		while (check == false) {
			std::cout << "Account doesn't exist. Re-enter: ";
			cin >> cid;
			if (to_cid.getCID() == cid) {
				check = true;
			}
		}
	}
	float nb = cb - m;
	if (cb >= 0) {
		std::cout << "Transaction successfully" << endl;
		message.push_back(to_string(m) + "T");
		transactions.push_back(nb);
		cb = nb;
		to_cid.cb += m;
		to_cid.message.push_back("You receive " + to_string(m));
		to_cid.transactions.push_back(to_cid.cb);
	}
	else {
		std::cout << "You don't have enough money, transaction unsuccessfully!";
		message.push_back("Transaction failed");
	}
	return cb;
}

void Customer::showInboxMessages() {
	for (int i = 0; i < message.size(); i++) {
		std::cout << message[i] << endl;
	}
	for (int k = 0; k < warning.size(); k++) {
		std::cout << warning[k] << endl;
	}
}

void Customer::lastNTransactions() {
	for (int i = 0; i < transactions.size(); i++) {
		std::cout << transactions[i] << endl;
	}
}

int rannum() {
	srand(time(nullptr));
	return rand() % 10000;
}

//randomly create the usernames for new customer
string username(string fn, string ln) {
	Admin a;
	string usn;
	int ran = rannum();
	usn = ln + fn + to_string(ran);
	for (Customer& c : cus) {
		for (Admin& a : ad) {
			while (usn == c.getUSN() || usn == a.getUSN()) {
				usn = ln + fn + to_string(ran);
			}
		}
	}
	return usn;
}

int rannumforid() {
	srand(time(nullptr));
	return rand() % 1000000000;
}

void signup() {
	Customer c;
	Admin a;
	int choose;
	std::cout << "1. Sign up for customer account: \n";
	std::cout << "2. Sign up for administration account: \n";
	cin >> choose;
	while (choose != 1 && choose != 2) {
		std::cout << "Reenter\n";
		std::cout << "1. Sign up for customer account: \n";
		std::cout << "2. Sign up for administration account: \n";
		cin >> choose;
	}
	long int ssn, cid, aid;
	float cb = 0, money;
	string ln, fn, org, dob, doj, pass1, pass2, usn;
	std::cout << "Enter your social security number: "; cin >> ssn;
	std::cout << "Enter your first name: "; cin >> fn;
	std::cout << "Enter your last name: "; cin >> ln;
	std::cout << "Enter your Organization: "; cin >> org;
	std::cout << "Enter your Date of Birth: "; cin >> dob;
	std::cout << "Enter your Date of Join: "; cin >> doj;
	std::cout << "Enter your New Password: "; cin >> pass1;
	std::cout << "Confirm your Password: "; cin >> pass2;
	while (pass2 != pass1) {
		std::cout << "Incorrect. Reconfirm: "; cin >> pass2;
	}
	usn = username(fn, ln);
	std::cout << "Please remember is your new username: " << usn << endl;
	if (choose == 1) {
		int cid = rannumforid();
		std::cout << "Make initial deposit: "; cin >> money;
		cb = c.deposit(money);
		//randomly generate new cid for new customers
		for (auto& cus : cus) {
			cid = rannumforid();
			while (cid == cus.getCID()) {
				cid = rannumforid();
			}
		}
		std::cout << "Your Customer ID is: " << cid << endl;
		c.setCID(cid);
		c.setCB(cb);
		c.setUSN(usn);
		c.setPass(pass1);
		c.setSSN(ssn);
		c.setFN(fn);
		c.setLN(ln);
		c.setORG(org);
		c.setDOB(dob);
		c.setDOJ(doj);
	}
	else {
		int aid = rannumforid();
		for (auto& ad : ad) {
			while (aid == ad.getAID()) {
				aid = rannumforid();
			}
		}
		std::cout << "Your Administor ID is: " << aid << endl;
		a.setAID(aid);
		a.setUSN(usn);
		a.setPass(pass1);
		a.setSSN(ssn);
		a.setFN(fn);
		a.setLN(ln);
		a.setORG(org);
		a.setDOB(dob);
		a.setDOJ(doj);
	}
	cus.emplace_back(cid, cb, usn, pass1, ssn, fn, ln, org, dob, doj);
	ad.emplace_back(aid, usn, pass1, ssn, fn, ln, org, dob, doj);
	std::cout << "Please log in again at Home Page!" << endl;
	std::exit(0);
}

void Cus_func() {
	Customer c;
	int n;
	std::cout << "1. Statement summary last N transactions" << endl;
	std::cout << "2. Current Balance" << endl;
	std::cout << "3. Withdraw" << endl;
	std::cout << "4. Deposit" << endl;
	std::cout << "5. Transfer to other CID" << endl;
	std::cout << "6. Check Inbox" << endl;
	std::cout << "7. Logout" << endl;
	std::cout << "Enter a number to continue (1-7): "; cin >> n;
	while (n < 1 || n > 7) {
		std::cout << "Invalid. Re-enter: "; cin >> n;
	}
	switch (n) {
	case 1:
		c.lastNTransactions();
		break;
	case 2:
	{
		float cb = 0.0;
		cb = c.lasttrans();
		std::cout << "Your current balance: " << cb;
	}
		break;
	case 3:
	{
		float out;
		std::cout << "How much do you want to have? \n"; cin >> out;
		c.withdrawal(out);
	}
		break;
	case 4:
	{
		float m;
		std::cout << "How much have you inputed? \n"; cin >> m;
		c.deposit(m);
	}
		break;
	case 5:
	{
		float t;
		int to_cid;
		std::cout << "Enter the customer's cid that you want to transfer to: "; cin >> to_cid;
		std::cout << "Enter the amount of money you want to transfer: "; cin >> t;
		c.transfer(t, to_cid);
	}
		break;
	case 6:
		c.showInboxMessages();
		break;
	case 7:
		std::exit(0);
		break;
	}
}

void cus_signin() {
	Customer c;
	string usn, pass;
	std::cout << "Enter username: "; cin >> usn;
	std::cout << "Enter password: "; cin >> pass;
	while (usn != c.getUSN() || pass != c.getPass()) {
		std::cout << "Re-enter username: "; cin >> usn;
		std::cout << "Re-enter password: "; cin >> pass;
	}
	if (c.countwarnings() >= 3) {
		std::cout << "You need to pay to continue the banking process\n";
		std::exit(0);
	}
	else {
		Cus_func();
	}
}

void Admin::generatesummaryreport() {
	ofstream myfile("users_info.txt", ios::app);
	if (myfile.is_open()) {
		for (Customer& customer : cus) {
			myfile << customer.getCID() << endl;
			myfile << customer.lasttrans() << endl;
			myfile << customer.getUSN() << endl;
			myfile << customer.getPass() << endl;
			myfile << customer.getSSN() << endl;
			myfile << customer.getFN() << endl;
			myfile << customer.getLN() << endl;
			myfile << customer.getORG() << endl;
			myfile << customer.getDOB() << endl;
			myfile << customer.getDOJ() << endl;
			myfile << "-----------------------------------" << endl;
		}
		myfile.close();
		std::cout << "Writing to file completed!";
	}
	else {
		std::cout << "File can't be opened!";
	}
}

void encrypt(string file) {
	int key;
	char c;
	std::cout << "key: "; cin >> key;
	fstream fin, fout;
	fin.open(file, fstream::in);
	fout.open("fileencrypted.txt", fstream::out);
	while (fin >> noskipws >> c) {
		int temp = (c + key);
		fout << (char)temp;
	}
	fin.close();
	fout.close();
}

void decrypt() {
	std::cout << "key: "; int k; cin >> k;
	char c;
	fstream fin, fout;
	fin.open("fileencrypted.txt", fstream::in);
	fout.open("decryptedfile.txt", fstream::out);
	while (fin >> noskipws >> c) {
		int temp = (c - k);
		fout << (char)temp;
	}
	fin.close();
	fout.close();
}

vector<string> Admin::checkBalancestatus() {
	vector<string> status;
	for (auto& customer : cus) {
		float cb = customer.lasttrans();
		if (cb >= 0) {
			status.push_back("positive");
			customer.deletewarning();
		}
		else {
			status.push_back("negative");
		}
	}
	return status;
}

float Admin::payInterest() {
	float totalInterest = 0.0;
	vector<string> status = checkBalancestatus();

	for (int i = 0; i < status.size(); i++) {
		if (status[i] == "positive") {
			for (auto& customer : cus) {
				float cb = customer.lasttrans();
				float interest = cb * 0.03;
				customer.push_backcb(cb + interest);
				totalInterest += interest;
			}
		}
	}
	std::cout << "Done paying interest\n";
	return totalInterest;
}

void Admin::sendwarning() {
	vector<string>status = checkBalancestatus();
	for (int i = 0; i < status.size(); i++) {
		if (status[i] == "negative") {
			for (auto& c : cus) {
				string message = "Your current ballance is negative. Please pay the money";
				c.push_backmessage(message);
			}
		}
	}
	std::cout << "Messages sent!" << endl;
}

void Admin::blockedaccounts() {
	ofstream report("negativeaccounts.txt", ios::app);
	if (report.is_open()) {
		for (auto& c : cus) {
			int i = c.countwarnings();
			if (i >= 3) {
				report << "You need to block these negative accounts. \n";
				report << c.getCID() << " " << c.getUSN() << " " << c.getCB() << endl;
			}
			report.close();
			std::cout << "Completed.";
		}
	}
	else {
		std::cout << "File can't be opened.";
	}

}

void ad_func() {
	Admin a;
	int choose;
	std::cout << "1. Pay Monthly Interest" << endl;
	std::cout << "2. Generate Summary Report" << endl;
	std::cout << "3. List of blocked accounts" << endl;
	std::cout << "4. Send warning" << endl;
	std::cout << "5. Log out" << endl;
	std::cout << "Enter an option from 1 to 5: "; cin >> choose;
	while (choose < 1 || choose > 5) {
		std::cout << "Re-enter: "; cin >> choose;
	}
	switch (choose) {
	case 1:
		a.payInterest();
		break;
	case 2:
		a.generatesummaryreport();
		break;
	case 3:
		a.blockedaccounts();
		break;
	case 4:
		a.sendwarning();
		break;
	case 5:
		std::exit(0);
		break;
	}
}

void ad_signin() {
	Admin a;
	string usn, pass;
	std::cout << "Enter username: "; cin >> usn;
	std::cout << "Enter password: "; cin >> pass;
	while (usn != a.getUSN() || pass != a.getPass()) {
		std::cout << "Re-enter username: "; cin >> usn;
		std::cout << "Re-enter password: "; cin >> pass;
	}

	ad_func();
}

int main() {
	int choose;
	std::cout << "**********Welcome to the Home Page of your banking account!**********" << endl;
	std::cout << "1. Admin Sign In" << endl;
	std::cout << "2. Customer Sign In" << endl;
	std::cout << "3. Sign up Page" << endl;
	std::cout << "4. Exit application" << endl;
	std::cout << "Enter your option from 1 to 4: "; cin >> choose;
	while (choose < 1 || choose > 4) {
		std::cout << "Re-enter: "; cin >> choose;
	}
	switch (choose) {
	case 1:
		ad_signin();
	case 2:
		cus_signin();
	case 3:
		signup();
	case 4:
		std::exit(0); 
	}
}
