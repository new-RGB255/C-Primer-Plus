#ifndef PASCALS_TRIANGLE_H
#define PASCALS_TRIANGLE_H

#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;

class pascalsTriangle {
public:

private:
	const int row;
	vector<vector<long>> res;
public:
	pascalsTriangle(int line_num = 0);
	~pascalsTriangle() {}
	void construct();
	void print();
};

#endif // !PASCALS_TRIANGLE_H
