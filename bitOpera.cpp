#include<iostream>
using namespace std;
int bitAdd(int a, int b);
int bitMinus(int a, int b);
int bitMultiply(int a, int b);
int bitDivide(int a, int b);
int bitNeg(int n);

int main(void)
{
	int a, b;
	cin >> a >> b;
	int ans;
	//ans = bitAdd(a, b);
	//ans = bitMinus(a, b);
	ans = bitMultiply(a, b);
	cout << ans << endl;
	return 0;
}

//int bitAdd(int a, int b)
//{
//	int ans = a;
//	while (b != 0)
//	{
//		ans = a ^ b;
//		//ans:a��b�޽�λ��ӵĽ��
//		b = (a & b) << 1;
//		//b:a��b���ʱ�Ľ�λ��Ϣ
//		a = ans;
//	}
//	return ans;
//}

//int bitNeg(int n)
//{
//	//һ�������෴�����ڸ����ķ����ټ�1(����)
//	return bitAdd(~n, 1);  
//}
//
//int bitMinus(int a, int b)
//{
//	//��ȥһ�����൱�ڼ��ϸ������෴��
//	return bitAdd(a, bitNeg(b));
//}

int bitMultiply(int a, int b)
{
	int ans = 0;
	while (b != 0);
	{
		if (b & 1)
		{
			ans = bitAdd(ans, a);
		}
		a <<= 1;
		b = (b >> 1) & bitMinus((1 << bitMinus(32, 1)), 1);
	}
	return ans;
}

int bitDivide(int a, int b)
{

}