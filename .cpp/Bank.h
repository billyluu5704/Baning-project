#pragma once
#ifndef Header_H
#define Header_H
#include "Header.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class User {
private:
	string ssn;
	string fn, ln, stat, org, dob, doj, pass, usn;
public:
	void setUSN(string USN) { usn = USN; }
	string getUSN() { return usn; }
	void setPass(string Pass) { pass = Pass; }
	string getPass() { return pass; }
	void setSSN(string SSN) { ssn = SSN; }
	string getSSN() { return ssn; }
	void setFN(string FN) { fn = FN; }
	void setLN(string LN) { ln = LN; }
	void setStat(string Stat) { stat = Stat; }
	void setORG(string ORG) { org = ORG; }
	void setDOB(string DOB) { dob = DOB; }
	void setDOJ(string DOJ) { doj = DOJ; }
	string getFN() { return fn; }
	string getLN() { return ln; }
	string getStat() { return stat; }
	string getORG() { return org; }
	string getDOB() { return dob; }
	string getDOJ() { return doj; }
	User() {}
	User(string USN, string Pass, string SSN, string Name, string ORG, string DOB,
		string DOJ, string LN, string FN) {
		setUSN(USN);
		setPass(Pass);
		setSSN(SSN);
		setFN(FN);
		setLN(LN);
		setORG(ORG);
		setDOB(DOB);
		setDOJ(DOJ);
	}
};

class Customer : public User {
private:
	long cid;
	float cb = 0;
	vector<string>message;
	vector<string>warning;
	vector<float>transactions;
public:
	void setCID(long CID) { cid = CID; }
	long getCID() { return cid; }
	void setCB(float CB) { cb = CB; }
	float getCB() { return cb; }
	Customer() {}
	Customer(long CID, float CB, string USN, string Pass, string SSN, string ORG, string DOB,
		string DOJ, string LN, string FN) {
		setCID(CID);
		setCB(CB);
		setUSN(USN);
		setPass(Pass);
		setSSN(SSN);
		setFN(FN);
		setLN(LN);
		setORG(ORG);
		setDOB(DOB);
		setDOJ(DOJ);
		message.push_back("Welcome to your banking account");
	}
	float withdrawal(float, Customer);
	float deposit(float, Customer);
	float transfer(float, long, Customer);
	void showInboxMessages(Customer);
	void lastNTransactions(Customer);
	float lasttrans(Customer) {
		int i = transactions.size();
		if (!transactions.empty()) {
			float cb = transactions[i - 1];
			return cb;
		}
		else {
			return 0.0;
		}
	}
	void push_backcb(float cb) {
		transactions.push_back(cb);
	}
	void push_backmessage(string mess) {
		warning.push_back(mess);
	}
	void deletewarning() {
		warning.clear();
	}
	int countwarnings() {
		return warning.size();
	}
};

class Admin :public User {
private:
	long aid;
public:
	void setAID(long AID) { aid = AID; }
	long getAID() { return aid; }
	Admin() {}
	Admin(long AID, string USN, string Pass, string SSN, string ORG, string DOB,
		string DOJ, string LN, string FN) {
		setAID(AID);
		setUSN(USN);
		setPass(Pass);
		setSSN(SSN);
		setFN(FN);
		setLN(LN);
		setORG(ORG);
		setDOB(DOB);
		setDOJ(DOJ);
	}
	float payInterest();
	void blockedaccounts();
	void sendwarning();
};
#endif // !1


