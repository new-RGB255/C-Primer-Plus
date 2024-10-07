#include "accabc.h"

using std::cout;
using std::endl;
using std::string;

void AccABC::Deposit(double amt) {
	if (amt < 0) {
		cout << "Negative deposit not allowed; "
			<< "deposit is cancelled.\n";
	}
	else {
		balance += amt;
	}
}

AccABC::Formatting AccABC::SetFormat() const {
	Formatting f;
	f.flag = cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	f.pr = cout.precision(2);
	return f;
}

void AccABC::Restore(AccABC::Formatting f) const {
	cout.setf(f.flag, std::ios_base::floatfield);
	cout.precision(f.pr);
}

void Brass::Withdraw(double amt) {
	if (amt < 0) {
		cout << "Withdrawal amount must be positive; "
			<< "Withdrawal canceled.\n";
	}
	else if (amt <= Balance()) {
		AccABC::Withdraw(amt);
	}
	else {
		cout << "Withdrawal amount of $" << amt
			<< "exceeds your balance.\n"
			<< "Withdrawal canceled.\n";
	}
}

void Brass::ViewAcct() const {
	Formatting f = SetFormat();
	cout << "Brass Client: " << FullName() << endl;
	cout << "Account Number: " << AcctNum() << endl;
	cout << "Balance: " << Balance() << endl;
	Restore(f);
}

void BrassPlus::ViewAcct() const {
	Formatting f = SetFormat();
	cout << "Brass Client: " << FullName() << endl;
	cout << "Account Number: " << AcctNum() << endl;
	cout << "Balance: " << Balance() << endl;
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to Bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%\n";
	Restore(f);
}

void BrassPlus::Withdraw(double amt) {
	Formatting f = SetFormat();
	double bal = AccABC::Balance();
	if (amt <= bal) {
		AccABC::Withdraw(amt);
	}
	else if (amt <= bal + maxLoan - owesBank) {
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;
		Deposit(advance);
		AccABC::Withdraw(amt);
	}
	else {
		cout << "Credit limit exceed. Transaction cancelled.\n";
	}
	Restore(f);
}
