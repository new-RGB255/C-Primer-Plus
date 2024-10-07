#ifndef _CLASSIC_CPP
#define _CLASSIC_CPP

#include<iostream>
#include "classic.h"

//class Cd {
//private:
//	char* performers;
//	char* label;
//	int selections;
//	double playtime;
//public:
//	Cd(char* s1 = nullptr, char* s2 = nullptr, int n = 0, double ptime = 0.0);
//	Cd(const Cd& d);
//	virtual ~Cd();
//	virtual void report() const;
//	virtual Cd& operator=(const Cd& d);
//};

Cd::Cd(const char* s1, const char* s2, int n, double ptime) {
	if (!s1 || !s2) {
		performers = nullptr;
		label = nullptr;
		selections = n;
		playtime = ptime;
		return;
	}
	int len1 = std::strlen(s1), len2 = std::strlen(s2);
	performers = new char[len1 + 1];
	label = new char[len2 + 1];
	std::strcpy(performers, s1);
	std::strcpy(label, s2);
	selections = n;
	playtime = ptime;
}

Cd::Cd(const Cd& d) {
	int len1 = std::strlen(d.performers), len2 = std::strlen(d.label);
	performers = new char[len1 + 1];
	label = new char[len2 + 1];
	std::strcpy(performers, d.performers);
	std::strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd::~Cd() {
	delete[] performers;
	delete[] label;
}

void Cd::report() const {
	std::cout << "Performers: " << performers << std::endl
		<< "Label: " << label << std::endl << "Selections: "
		<< selections << std::endl << "Playtime: "
		<< playtime << std::endl;
}

Cd& Cd::operator=(const Cd& d) {
	if (this == &d) return *this;
	int len1 = std::strlen(d.performers), len2 = std::strlen(d.label);
	delete[] performers;
	delete[] label;
	performers = new char[len1 + 1];
	label = new char[len2 + 1];
	std::strcpy(performers, d.performers);
	std::strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
	return *this;
}

//class Classic :public Cd {
//private:
//	char* string;
//public:
//	Classic(const char* st = nullptr, const char* s1 = nullptr,
//		const char* s2 = nullptr, int n = 0, double ptime = 0.0);
//	Classic(const Classic& cl);
//	virtual ~Classic();
//	virtual void report() const;
//	Classic& operator=(const Classic& cl);
//};

Classic::Classic(const char* st, const char* s1, const char* s2,
	int n, double ptime) :Cd(s1, s2, n, ptime) {
	if (!st) {
		string = nullptr;
		return;
	}
	int len = std::strlen(st);
	string = new char[len + 1];
	std::strcpy(string, st);
}

Classic::Classic(const Classic& cl) :Cd(cl) {
	int len = std::strlen(string);
	string = new char[len + 1];
	std::strcpy(string, cl.string);
}

Classic::~Classic() {
	delete[] string;
}

void Classic::report() const {
	std::cout << "String: " << string << std::endl;
	Cd::report();
}

Classic& Classic::operator=(const Classic& cl) {
	if (this == &cl) return *this;
	Cd::operator=(cl);
	int len = std::strlen(cl.string);
	delete[] string;
	string = new char[len + 1];
	std::strcpy(string, cl.string);
	return *this;
}


#endif // !_CLASSIC_CPP
