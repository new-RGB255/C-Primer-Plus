#pragma once
#ifndef _CLASSIC_H
#define _CLASSIC_H

class Cd {
private:
	char* performers;
	char* label;
	int selections;
	double playtime;
public:
	Cd(const char* s1 = nullptr, const char* s2 = nullptr, 
		int n = 0, double ptime = 0.0);
	Cd(const Cd& d);
	virtual ~Cd();
	virtual void report() const;
	virtual Cd& operator=(const Cd& d);
};

class Classic :public Cd {
private:
	char* string;
public:
	Classic(const char* st = nullptr, const char* s1 = nullptr,
		const char* s2 = nullptr, int n = 0, double ptime = 0.0);
	Classic(const Classic& cl);
	virtual ~Classic();
	virtual void report() const;
	virtual Classic& operator=(const Classic& cl);
};


#endif // !_CLASSIC_H
