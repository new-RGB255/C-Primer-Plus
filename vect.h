#ifndef VECTOR_H_
#define VECTOR_H_
#include<iostream>

namespace VECTOR {
	class Vector {
	public:
		//用枚举设置符号常量(很关键,将枚举设置在类中,避免使用全局变量)
		enum Mode {
			RECT, POL  //直角坐标,极坐标
		};
	private:
		//直角坐标
		double x; //横坐标
		double y; //纵坐标
		//极坐标
		double mag; //极径
		double ang; //极角
		//模式切换
		Mode mode;
		//坐标赋值
		void set_x();
		void set_y();
		void set_mag();
		void set_ang();
	public:
		Vector();
		~Vector();
		Vector(double n1, double n2, Mode form = RECT);
		//重置可直接修改对象的私有成员而不通过非默认构造函数,减少额外步骤
		void reset(double n1, double n2, Mode form = RECT);
		//返回坐标
		double x_val() const { return x; }
		double y_val() const { return y; }
		double mag_val() const { return mag; }
		double ang_val() const { return ang; }
		//设置显示模式
		void rect_mode();
		void pol_mode();
		//重载运算符
		Vector operator+(const Vector& b) const;
		Vector& operator+=(const Vector& b);
		Vector operator-(const Vector& b) const;
		void operator-=(const Vector& b);
		Vector operator-() const; //取反
		Vector operator*(double n) const;
		void operator*=(double n);
		double operator^(const Vector& b) const; //点乘
		double operator*(const Vector& b) const; //叉乘
		//友元
		friend Vector operator*(double n, const Vector& a);	
		friend std::ostream& operator<<(std::ostream& os, const Vector& v);
	};

} //end namespace VECTOR

#endif // !VECTOR_H_
