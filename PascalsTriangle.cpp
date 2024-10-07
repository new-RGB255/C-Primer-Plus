#include "PascalsTriangle.h"
using std::cout;
using std::endl;

pascalsTriangle::pascalsTriangle(int line_num) :row(line_num) {
	for (int i = 0; i < row; ++i) {
		vector<long> ves;
		for (int j = 0; j < row; ++j) {
			ves.push_back(0);
		}
		res.push_back(ves);
	}
}

void pascalsTriangle::construct() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == i) {
				res[i][j] = 1;
			}
			else{
				res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
			}
		}
	}
}

void pascalsTriangle::print() {
	string* result = new string[row];
	for (int i = 0; i < row; ++i) {
		for (int num = row - i; num > 0; --num) {
			int count = std::to_string(res[row - 1][row / 2]).size();
			while (count--) {
				result[i] += ' ';
			}
		}
		for (int j = 0; j <= i; ++j) {
			result[i] += std::to_string(res[i][j]);
			if (j < i){
				if (std::to_string(res[i][j]).size() ==
					std::to_string(res[row - 1][row / 2]).size()) {
					int count = std::to_string(res[row - 1][row / 2]).size();
					while (count--) {
						result[i] += ' ';
					}
				}
				else if (std::to_string(res[i][j]).size() > 1 &&
					std::to_string(res[i][j + 1]).size() != 1) {
					int count = std::to_string(res[row - 1][row / 2]).size() +
						(std::to_string(res[row - 1][row / 2]).size() -
							std::to_string(res[i][j]).size());
					while (count--) {
						result[i] += ' ';
					}
				}
				else if (std::to_string(res[i][j]).size() > 1 &&
					std::to_string(res[i][j + 1]).size() <
					std::to_string(res[i][j]).size()) {
					int count = std::to_string(res[row - 1][row / 2]).size() +
						(std::to_string(res[row - 1][row / 2]).size() - 3) +
						(std::to_string(res[i][j]).size() - 
							std::to_string(res[i][j + 1]).size());
					while (count--) {
						result[i] += ' ';
					}
				}
				else{
					for (int count = 1; count <= 2 *
						std::to_string(res[row - 1][row / 2]).size() - 1; ++count) {
						result[i] += ' ';
					}
				}
			}
		}
		cout << result[i];     
		cout << endl;
	} 
	delete[] result;
}
