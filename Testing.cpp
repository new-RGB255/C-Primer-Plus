#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	using fakedSTL::arrayList;
	using fakedSTL::unionFindNode;

	vector<string> vt = { "jigfdjg","Dsofo","jaig43","DJHldslfj" };
	unionFindNode<string> ufn(vt);
	cout << ufn.getNum() << endl;
	ufn.unite("jigfdjg", "DJHldslfj");
	cout << ufn.getHeight("DJHldslfj") << " " << ufn.getHeight("jigfdjg") << endl;
	ufn.unite("DJHldslfj", "Dsofo");
	cout << ufn.getNum() << endl;
	cout << ufn.getHeight("jigfdjg") << " " << ufn.getHeight("Dsofo") << endl;
	

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
