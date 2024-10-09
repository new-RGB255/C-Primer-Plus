#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	using fakedSTL::arrayList;

	vector<int> res{ 2,4,6,7,32,5,22,5 ,239,464,12,34535,53,22 };
	size_t len = res.size() - 1;
	fakedSTL::quickSort(res, 0, len);
	for (auto num : res) {
		cout << num << " ";
	}
	cout << endl;

	

	/*arrayList<int> test;

	test.insert(0, 1);
	test.insert(1, 2);
	test.insert(2, 3);
	test.insert(3, 4);
	test.insert(4, 5);
	test.insert(5, 6);
	test.insert(6, 7);
	test.insert(7, 6);
	test.insert(8, 6);
	test.insert(9, 6);
	test.insert(10, 67);

	test.erase(2);
	test.erase(2);
	
	test.erase(2);
	test.erase(2);
	test.erase(2);
	

	

	cout << test;*/
	
	

	return 0;
}
