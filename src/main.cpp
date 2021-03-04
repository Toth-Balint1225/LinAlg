#include <iostream>
#include "rational.h" 
#include "matrix.h"
// scope:
// - vector operations (override operators)
// - matrix operatons
// - base transformation!

int main() {
	std::cout << "Hello World" << std::endl;
	Rational r1(1,10);
	Rational r2(2,5);
	Rational r3(2,1);
	Rational r4(0,1);
	std::cout << r1 << " " << r2 << " " << r3 << std::endl;
	std::cout << r1*r2 << " " << r1/r3 << std::endl;
	std::cout << r1+r2 << " " << r1-r3 << std::endl;
	std::cout << (r1 <= r2) << std::endl;
	Matrix m(2,3);  // 2 rows, 3 columns
	m.setElement(0,0,1.0f);
	m.setElement(0,1,1.1f);
	m.setElement(0,2,1.2f);
	m.setElement(1,0,2.0f);
	m.setElement(1,1,2.1f);
	m.setElement(1,2,2.2f);
	std::cout << m << std::endl;
	Matrix<Rational>* m2 = new Matrix<Rational>(2,3);
	m2->setElement(0,0,r1);
	m2->setElement(0,1,r2);
	m2->setElement(0,2,r1);
	m2->setElement(1,0,r3);
	m2->setElement(1,1,r1);
	m2->setElement(1,2,r4);
	std::cout << *m2 << std::endl;
	delete m2;
	std::cout << std::endl;
	return 0;
}

