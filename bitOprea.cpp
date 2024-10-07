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
		//ans:a和b无进位相加的结果
		ans = a ^ b;
		//b:a和b相加时的进位信息
		b = (a & b) << 1;
		a = ans;
	}
	return ans;
}

int bitNeg(int n)
{
	//一个数的相反数等于该数的反码再加1(即补码)
	return bitAdd(~n, 1);  
}

int bitMinus(int a, int b)
{
	//减去一个数相当于加上该数的相反数
	return bitAdd(a, bitNeg(b));
}

int bitMultiply(int a, int b)
{
	int ans = 0;
	while (b != 0)
	{
		if (b & 1)
		{
			//考察b当前最右边一位的状态,若为1则执行下面的加法
			ans = bitAdd(ans, a);
		}
		a <<= 1;
		//b这个数字无符号右移i位 = 
		// b有符号右移i位 & bitMinus((1 << bitMinus(32, i)), 1)
		b = (b >> 1) & bitMinus((1 << bitMinus(32, 1)), 1); 
		//这里以32位int类型为例,在int范围以内计算结果均正确
		//用掩码思想使得b右移一位后在最高位添0
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
		//a是整数最小,b也是整数最小,返回1
		return 1;
	}
	else if (a != INT32_MIN && b != INT32_MIN)
	{
		//正常除法
		return bitDiv(a, b);
	}
	else if (b == INT32_MIN)
	{
		//a不是整数最小,但b是整数最小,返回0
		return 0;
	}
	else if (a == INT32_MIN && b == bitNeg(1))
	{
		//a是整数最小,b为-1,返回整数最大
		return INT32_MAX;
	}
	else {
		//a是整数最小,但b不是整数最小且b不为-1
		a = bitAdd(a, b > 0 ? b : bitNeg(b));
		//要让a变得没那么小以便通过bitDiv()处理数据
		//a通过加上|b|使得a变大一些
		int ans = bitDiv(a, b);
		//若b>0,则ans偏大,最后减个1;若b<0,则ans偏小,最后加个1
		int offset = b > 0 ? bitNeg(1) : 1;
		return bitAdd(ans, offset);
	}
}