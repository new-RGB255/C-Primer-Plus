//#include<iostream>
//#include<cstdlib>
//#include<ctime>
//#include "vect.h"
//
//int main(void) {
//	srand(time(0));
//	double direction;
//	VECTOR::Vector step;
//	VECTOR::Vector result(0.0, 0.0); //隐式调用
//	//VECTOR::Vector result = VECTOR::Vector(0.0, 0.0); //显示调用
//	unsigned long steps = 0;
//	double target, dstep;
//	std::cout << "Enter target distance (q to quit): ";
//	while (std::cin >> target) {
//		std::cout << "Enter step length:";
//		if (!(std::cin >> dstep)) {
//			break;
//		}
//
//		while (result.mag_val() < target) {
//			direction = rand() % 360;
//			step.reset(dstep, direction, VECTOR::Vector::POL);
//			result += step;
//			++steps;
//		}
//		std::cout << "After " << steps << " steps,the subjet "
//			"has the following location:\n";
//		std::cout << result << std::endl;
//		result.pol_mode();
//		std::cout << "or\n" << result << std::endl;
//		std::cout << "Average outward distance per step = "
//			<< result.mag_val() / steps << std::endl;
//		steps = 0;
//		result.reset(0.0, 0.0);
//		std::cout << "Enter target distance (q to quit): ";
//	}
//	std::cout << "Bye!\n";
//	std::cin.clear();
//	while (std::cin.get() != '\n') {
//		continue;
//	}
//	return 0; 
//}