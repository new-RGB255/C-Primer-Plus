#pragma once
#ifndef _ACC_ABC_H
#define _ACC_ABC_H

#include<iostream>
#include<string>
using std::string;

class AccABC {
private:
	string fullName;
	long acctNum;
	double balance;
protected:
	struct Formatting {
		std::ios_base::fmtflags flag;
		std::streamsize pr;
	};
	const string& FullName() const { return fullName; }
	long AcctNum() const { return acctNum; }
	Formatting SetFormat() const;
	void Restore(Formatting f) const;
public:
	AccABC(const string& s = "Nullbody", long an = -1, double bal = 0.0) :
		fullName(s), acctNum(an), balance(bal) {}
	virtual ~AccABC() {}
	void Deposit(double amt);
	virtual void Withdraw(double amt) = 0 { balance -= amt; }
	double Balance() const { return balance; }
	virtual void ViewAcct() const = 0 {}
};
/*

*/
class Brass :public AccABC {
public:
	Brass(const string& s = "Nullbody", long an = -1, double bal = 0.0) :
		AccABC(s, an, bal) {}
	virtual void Withdraw(double amt);
	virtual void ViewAcct() const;
	virtual ~Brass() {}
};
/*
	C++允许一个类继承多个类,
	但若有同名函数要写全函数各自的类作用域;
	然而,当继承的多个类中有共同的基类时,为基类指针与引用
	赋值时会出现二义性,因为这样会有多个转换函数匹配
	*******************************************************************
	比如基类A,派生类B和C(B和C都继承A);
	class A {
		...
	}
	class B :public A {
		...
	}
	class C :public A, public B {
		...
	}
	此时若C的对象赋值给A的指针或引用将产生二义性,因为此时也能将
	C的对象赋值给B的指针或引用;
	若B不是由A派生出,则class C :public A, public B 合法;
*/
class BrassPlus :public AccABC {
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const string& s = "Nullbody", long an = -1, double bal = 0.0,
		double ml = 500, double r = 0.11125) :
		AccABC(s, an, bal), maxLoan(ml), rate(r), owesBank(0.0) {}
	BrassPlus(const Brass& ba, double ml = 500, double r = 0.11125) :
		AccABC(ba), maxLoan(ml), rate(r), owesBank(0.0) {}
	virtual ~BrassPlus() {};
	virtual void ViewAcct() const;
	virtual void Withdraw(double amt);
	void ResetMax(double m) { maxLoan = m; }
	void ResetRate(double r) { rate = r; }
	void ResetOwes() { owesBank = 0; }
};

#endif // !_ACC_ABC_H
