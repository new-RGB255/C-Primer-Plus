#ifndef VECTOR_H_
#define VECTOR_H_
#include<iostream>

namespace VECTOR {
	class Vector {
	public:
		//��ö�����÷��ų���(�ܹؼ�,��ö������������,����ʹ��ȫ�ֱ���)
		enum Mode {
			RECT, POL  //ֱ������,������
		};
	private:
		//ֱ������
		double x; //������
		double y; //������
		//������
		double mag; //����
		double ang; //����
		//ģʽ�л�
		Mode mode;
		//���긳ֵ
		void set_x();
		void set_y();
		void set_mag();
		void set_ang();
	public:
		Vector();
		~Vector();
		Vector(double n1, double n2, Mode form = RECT);
		//���ÿ�ֱ���޸Ķ����˽�г�Ա����ͨ����Ĭ�Ϲ��캯��,���ٶ��ⲽ��
		void reset(double n1, double n2, Mode form = RECT);
		//��������
		double x_val() const { return x; }
		double y_val() const { return y; }
		double mag_val() const { return mag; }
		double ang_val() const { return ang; }
		//������ʾģʽ
		void rect_mode();
		void pol_mode();
		//���������
		Vector operator+(const Vector& b) const;
		Vector& operator+=(const Vector& b);
		Vector operator-(const Vector& b) const;
		void operator-=(const Vector& b);
		Vector operator-() const; //ȡ��
		Vector operator*(double n) const;
		void operator*=(double n);
		double operator^(const Vector& b) const; //���
		double operator*(const Vector& b) const; //���
		//��Ԫ
		friend Vector operator*(double n, const Vector& a);	
		friend std::ostream& operator<<(std::ostream& os, const Vector& v);
	};

} //end namespace VECTOR

#endif // !VECTOR_H_
