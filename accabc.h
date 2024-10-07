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
	C++����һ����̳ж����,
	������ͬ������Ҫдȫ�������Ե���������;
	Ȼ��,���̳еĶ�������й�ͬ�Ļ���ʱ,Ϊ����ָ��������
	��ֵʱ����ֶ�����,��Ϊ�������ж��ת������ƥ��
	*******************************************************************
	�������A,������B��C(B��C���̳�A);
	class A {
		...
	}
	class B :public A {
		...
	}
	class C :public A, public B {
		...
	}
	��ʱ��C�Ķ���ֵ��A��ָ������ý�����������,��Ϊ��ʱҲ�ܽ�
	C�Ķ���ֵ��B��ָ�������;
	��B������A������,��class C :public A, public B �Ϸ�;
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
