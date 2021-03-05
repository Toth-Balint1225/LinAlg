#include <iostream>
#include "rational.h" 
#include "matrix.h"
#include "real.h"
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
	Matrix<Rational>* m2 = new Matrix<Rational>(2,3);
	m2->setElement(0,0,r1);
	m2->setElement(0,1,r2);
	m2->setElement(0,2,r1);
	m2->setElement(1,0,r3);
	m2->setElement(1,1,r1);
	m2->setElement(1,2,r4);
	std::cout << *m2 << std::endl;
	std::cout << *m2 << "+\n" << *m2 << "=\n" << m2->add(*m2) << std::endl;
	std::cout << "2\n*\n" << *m2 << "=\n" << multiplyByScalar(Rational(2,1),*m2);
	delete m2;
	Real re1(1.0f);
	Real re2(2.0f);
	std::cout << re1 << " " << re2 << " " << re1*re2 << " " << re1 - re2 << " " << Real::null() << " " << Real::unit() << std::endl;
	std::cout << Rational::null() << " " << Rational::unit() << std::endl;

	Matrix m3(3,4);
	m3.setElement(0,0,Real(2.0f));
	m3.setElement(0,1,Real(0.0f));
	m3.setElement(0,2,Real(1.0f));
	m3.setElement(0,3,Real(3.0f));
	m3.setElement(1,0,Real(1.0f));
	m3.setElement(1,1,Real(1.0f));
	m3.setElement(1,2,Real(0.0f));
	m3.setElement(1,3,Real(4.0f));
	m3.setElement(2,0,Real(2.0f));
	m3.setElement(2,1,Real(1.0f));
	m3.setElement(2,2,Real(4.0f));
	m3.setElement(2,3,Real(0.0f));
	Matrix m4(4,2);
	m4.setElement(0,0,Real(1.0f));
	m4.setElement(0,1,Real(4.0f));
	m4.setElement(1,0,Real(0.0f));
	m4.setElement(1,1,Real(2.0f));
	m4.setElement(2,0,Real(1.0f));
	m4.setElement(2,1,Real(1.0f));
	m4.setElement(3,0,Real(3.0f));
	m4.setElement(3,1,Real(1.0f));
	std::cout << m3 << "\n*\n"<< m4 << "\n=" << std::endl;
	std::cout << m3.multiply(m4)  << std::endl;
	std::cout << Matrix<Real>::unit(3) << std::endl << Matrix<Real>::null(4) << std::endl;
	std::cout << Matrix<Rational>::unit(3) << std::endl << Matrix<Rational>::null(4) << std::endl;
	try {
		std::cout << m4.multiply(m3) << std::endl;
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;	
	}
	Matrix<Rational> m5(3,4);
	m5.setElement(0,0,Rational(1,10));
	m5.setElement(0,1,Rational(2,3));
	m5.setElement(0,2,Rational(4,3));
	m5.setElement(0,3,Rational(5,6));
	m5.setElement(1,0,Rational(1,2));
	m5.setElement(1,1,Rational(12,4));
	m5.setElement(1,2,Rational(1,1));
	m5.setElement(1,3,Rational(0,1));
	m5.setElement(2,0,Rational(5,7));
	m5.setElement(2,1,Rational(4,3));
	m5.setElement(2,2,Rational(2,3));
	m5.setElement(2,3,Rational(8,5));
	Matrix<Rational> m6(4,2);
	m6.setElement(0,0,Rational(6,7));
	m6.setElement(0,1,Rational(4,6));
	m6.setElement(1,0,Rational(9,4));
	m6.setElement(1,1,Rational(11,2));
	m6.setElement(2,0,Rational(20,3));
	m6.setElement(2,1,Rational(1,2));
	m6.setElement(3,0,Rational(4,5));
	m6.setElement(3,1,Rational(6,6));
	std::cout << m5 << "\n*\n"<< m6 << "\n=" << std::endl;
	try {
		std::cout << m5 * m6  << std::endl;
		std::cout << m6 * m5 << std::endl;
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;	
	}
	std::cout << (Real(1.2) + Real(9.4) * Real(2.3)) << std::endl;
	std::cout << (Rational(1,2) + Rational(18,12)) << std::endl;

	Matrix<Rational> uj = m5;
	std::cout << uj << std::endl;
	uj = m6;
	std::cout << uj << std::endl;

	std::cout << std::endl;
	std::cout << m5 << std::endl << m5.submatrix(0,0) << std::endl;

	Matrix detm(3,3);
	detm.setElement(0,0,Real(1.0f));
	detm.setElement(0,1,Real(3.0f));
	detm.setElement(0,2,Real(4.0f));
	detm.setElement(1,0,Real(2.0f));
	detm.setElement(1,1,Real(1.0f));
	detm.setElement(1,2,Real(0.0f));
	detm.setElement(2,0,Real(6.0f));
	detm.setElement(2,1,Real(2.0f));
	detm.setElement(2,2,Real(1.0f));

	Matrix<Rational> detm2(3,3);
	detm2.setElement(0,0,Rational(1,1));
	detm2.setElement(0,1,Rational(3,1));
	detm2.setElement(0,2,Rational(4,1));
	detm2.setElement(1,0,Rational(2,1));
	detm2.setElement(1,1,Rational(1,1));
	detm2.setElement(1,2,Rational(0,1));
	detm2.setElement(2,0,Rational(6,1));
	detm2.setElement(2,1,Rational(2,1));
	detm2.setElement(2,2,Rational(1,1));

	std::cout << "det\n" << detm << std::endl << "=" << detm.det() << std::endl;
	std::cout << "det\n" << detm2 << std::endl << "=" << detm2.det() << std::endl;

	return 0;

}

