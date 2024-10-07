#include<cmath>
#include "vect.h"

namespace VECTOR {

	const double Rad_to_deg = 45.0 / atan(1.0);	
	//私有
	//坐标赋值
	void Vector::set_x() {
		x = mag * cos(ang);
	}

	void Vector::set_y() {
		y = mag * sin(ang);
	}

	void Vector::set_mag() {
		mag = sqrt(x * x + y * y);
	}

	void Vector::set_ang() {
		if (x == 0.0 && y == 0.0) {
			ang = 0.0;
		}
		else {
			ang = atan2(y, x);
		}
	}

	//公有
	//构造函数
	Vector::Vector() {
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	Vector::Vector(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			std::cout << "Incorrent 3rd argument to Vector() -- ";
			std::cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	//析构函数
	Vector::~Vector() {}

	//重置
	void Vector::reset(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			std::cout << "Incorrent 3rd argument to Vector() -- ";
			std::cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	//设置显示模式
	void Vector::rect_mode() {
		mode = RECT;
	}

	void Vector::pol_mode() {
		mode = POL;
	}

	//重载运算符
	Vector Vector::operator+(const Vector& b) const {
		return Vector(x + b.x, y + b.y);
	}

	Vector& Vector::operator+=(const Vector& b) {
		x += b.x;
		y += b.y;
		set_mag();
		set_ang();
		mode = RECT;
		return *this;
	}

	Vector Vector::operator-(const Vector& b) const {
		return Vector(x - b.x, y - b.y);
	}

	void Vector::operator-=(const Vector& b) {
		x -= b.x;
		y -= b.y;
		set_mag();
		set_ang();
		mode = RECT;
	}

	Vector Vector::operator-() const {
		return Vector(-x, -y);
	}

	Vector Vector::operator*(double n) const {
		return Vector(n * x, n * y);
	}

	void Vector::operator*=(double n) {
		x *= n;
		y *= n;
		set_mag();
		set_ang();
		mode = RECT;
	}

	double Vector::operator^(const Vector& b) const {
		return x * b.x + y * b.y;
	}

	double Vector::operator*(const Vector& b) const {
		return x * b.y - y * b.x;
	}

	//友元
	Vector operator*(double n, const Vector& a) {
		return a * n;
	}

	std::ostream& operator<<(std::ostream& os, const Vector& v) {
		if (v.mode == Vector::RECT) {
			os << "(x,y) = (" << v.x << "," << v.y << ")";
		}
		else if (v.mode == Vector::POL) {
			os << "(m,a) = (" << v.mag << "," << v.ang * Rad_to_deg << ")";
		}
		else {
			os << "Vector object mode is invalid";
		}
		return os;
	}

} //end namespace VECTOR
