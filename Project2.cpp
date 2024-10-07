//#include<iostream>
//#include<climits>
//#include<cstdlib>
//#include "bitOprea.h"
//using namespace std;
//unsigned int rotate_l(unsigned int x, int num);
//
//int main(void)
//{
//	unsigned int x;
//	cout << "Enter:";
//	cin >> x;
//	int num;
//	cout << "Enter:";
//	cin >> num;
//	x = rotate_l(x, num);
//	cout << x;
//	
//	
//	return 0;
//}
//
//unsigned int rotate_l(unsigned int x, int num)
//{
//	int size = CHAR_BIT * sizeof(unsigned int);
//	if (num > size || num < 0)
//	{
//		cout << "ERROR" << endl;
//		exit(EXIT_FAILURE);
//	}
//	for (int i = 0; i < num; i = bitAdd(i, 1))
//	{
//		if (x & (1 << bitMinus(size, 1)))
//		{
//			x <<= 1;
//			x |= 1;
//		}
//		else {
//			x <<= 1;
//		}
//	}
//	
//	return x;
//}