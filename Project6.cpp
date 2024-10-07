//#include<iostream>
//#include "classic.h"
//
//void Bravo(const Cd& disk);
//
//int main(void) {
//
//	using namespace std;
//
//	Cd c1("Beatles", "Capitol", 14, 35.5);
//	Classic c2("Piano Sonata in B flat, Fantasia in C",
//		"Alfred Brendel", "Philips", 2, 57.17);
//	
//	Cd* pcd = &c1;
//	cout << "Using object directly:\n";
//	c1.report();
//	cout << endl;
//	c2.report();
//	cout << endl;
//	cout << "Using type Cd* pointer to objects:\n";
//	pcd->report();
//	cout << endl;
//	pcd = &c2;
//	pcd->report();
//	cout << endl;
//	cout << "Calling a function with a Cd reference argument:\n";
//	Bravo(c1);
//	cout << endl;
//	Bravo(c2);
//	cout << endl;
//	cout << "Testing assignment: ";
//	Classic copy;
//	copy = c2;
//	copy.report();
//
//	return 0;
//}
//
//void Bravo(const Cd& disk) {
//	disk.report();
//}
