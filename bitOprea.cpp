#include<iostream>
#include<climits>
#include<cstdlib>
#include "bitOprea.h"
using namespace std;

//int main(void)
//{
//	int a, b;
//	cin >> a >> b;
//	int ans;
//	ans = bitAdd(a, b);
//	ans = bitMinus(a, b);
//	ans = bitMultiply(a, b);
//	ans = bitDivide(a, b);
//	cout << ans << endl;
//	return 0;
//}

int bitAdd(int a, int b)
{
	int ans = a;
	while (b != 0)
	{
		//ans:a��b�޽�λ��ӵĽ��
		ans = a ^ b;
		//b:a��b���ʱ�Ľ�λ��Ϣ
		b = (a & b) << 1;
		a = ans;
	}
	return ans;
}

int bitNeg(int n)
{
	//һ�������෴�����ڸ����ķ����ټ�1(������)
	return bitAdd(~n, 1);  
}

int bitMinus(int a, int b)
{
	//��ȥһ�����൱�ڼ��ϸ������෴��
	return bitAdd(a, bitNeg(b));
}

int bitMultiply(int a, int b)
{
	int ans = 0;
	while (b != 0)
	{
		if (b & 1)
		{
			//����b��ǰ���ұ�һλ��״̬,��Ϊ1��ִ������ļӷ�
			ans = bitAdd(ans, a);
		}
		a <<= 1;
		//b��������޷�������iλ = 
		// b�з�������iλ & bitMinus((1 << bitMinus(32, i)), 1)
		b = (b >> 1) & bitMinus((1 << bitMinus(32, 1)), 1); 
		//������32λint����Ϊ��,��int��Χ���ڼ���������ȷ
		//������˼��ʹ��b����һλ�������λ��0
	}
	return ans;
}

int bitDiv(int a, int b)
{
	int x = a < 0 ? bitNeg(a) : a;
	int y = b < 0 ? bitNeg(b) : b;
	int ans = 0;
	for (int i = 30; i >= 0; i = bitMinus(i, 1))
	{
		if ((x >> i) >= y)
		{
			ans |= (1 << i);
			x = bitMinus(x, y << i);
		}
	}
	return (a < 0) ^ (b < 0) ? bitNeg(ans) : ans;
}

int bitDivide(int a, int b)
{
	if (b == 0)
	{
		cout << "ERROR" << endl;
		exit(EXIT_FAILURE);
	}
	else if (a == INT32_MIN && b == INT32_MIN)
	{
		//a��������С,bҲ��������С,����1
		return 1;
	}
	else if (a != INT32_MIN && b != INT32_MIN)
	{
		//��������
		return bitDiv(a, b);
	}
	else if (b == INT32_MIN)
	{
		//a����������С,��b��������С,����0
		return 0;
	}
	else if (a == INT32_MIN && b == bitNeg(1))
	{
		//a��������С,bΪ-1,�����������
		return INT32_MAX;
	}
	else {
		//a��������С,��b����������С��b��Ϊ-1
		a = bitAdd(a, b > 0 ? b : bitNeg(b));
		//Ҫ��a���û��ôС�Ա�ͨ��bitDiv()��������
		//aͨ������|b|ʹ��a���һЩ
		int ans = bitDiv(a, b);
		//��b>0,��ansƫ��,������1;��b<0,��ansƫС,���Ӹ�1
		int offset = b > 0 ? bitNeg(1) : 1;
		return bitAdd(ans, offset);
	}
}