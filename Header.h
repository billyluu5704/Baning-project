#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class User {
private:
	int ssn;
	string fn, ln, stat, org, dob, doj, pass, usn;
public:
	void setUSN(string USN) { usn = USN; }
	string getUSN() { return usn; }
	void setPass(string Pass) { pass = Pass; }
	string getPass() { return pass; }
	void setSSN(int SSN) { ssn = SSN; }
	int getSSN() { return ssn; }
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
	User(string USN, string Pass, int SSN, string Name, string ORG, string DOB,
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
	int cid;
	float cb = 0;
	vector<string>message;
	vector<string>warning;
	vector<float>transactions;
public:
	void setCID(int CID) { cid = CID; }
	int getCID() { return cid; }
	void setCB(float CB) { cb = CB; }
	float getCB() { return cb; }
	Customer() {}
	Customer(int CID, float CB, string USN, string Pass, int SSN, string ORG, string DOB,
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
	float withdrawal(float);
	float deposit(float);
	float transfer(float, int );
	void showInboxMessages();
	void lastNTransactions();
	float lasttrans() {
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
	int aid;
public:
	void setAID(int AID) { aid = AID; }
	int getAID() { return aid; }
	Admin() {}
	Admin(int AID, string USN, string Pass, int SSN, string ORG, string DOB,
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
	vector<string> checkBalancestatus();
	void generatesummaryreport();
	void blockedaccounts();
	void sendwarning();
};


