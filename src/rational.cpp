#include "rational.h"
#include <algorithm>

Rational::Rational():
	numerator(0), denominator(1) {
}

Rational::Rational (int _numerator, int _denominator):
	numerator(_numerator), denominator(_denominator) {
}

Rational::Rational (const Rational& other):
	numerator(other.numerator), denominator(other.denominator) {
}

Rational::~Rational() {
}


Rational Rational::addTo(Rational& other) {
	int common = lcm(this->denominator,other.denominator);	
	Rational toReturn(this->numerator*((int)common/this->denominator) 
			+ other.numerator*((int)common/other.denominator)
			, common);
	toReturn.simplify();
	return toReturn;
}

Rational Rational::subtract(Rational& other) {
	Rational negated(other.negate());
	return addTo(negated);
}

Rational Rational::negate() {
	return Rational(-numerator, denominator);
}

Rational Rational::invert() {
	return Rational(denominator, numerator);
}

Rational Rational::multiplyBy(Rational& other) {
	Rational toReturn(this->numerator*other.numerator, this->denominator*other.denominator);
	toReturn.simplify();
	return toReturn;
}

Rational Rational::divideBy(Rational& other) {
	Rational inverted(other.invert());
	return multiplyBy(inverted);
}

Rational Rational::operator +(Rational& other) {
	return addTo(other);
}

Rational Rational::operator -(Rational& other) {
	return subtract(other);
}

Rational Rational::operator *(Rational& other) {
	return multiplyBy(other);
}

Rational Rational::operator /(Rational& other) {
	return divideBy(other);
}


bool Rational::operator <=(const Rational& other) {
	int common = lcm(this->denominator,other.denominator);
	return (this->numerator*((int)common/this->denominator)) <= (other.numerator*((int)common/other.denominator));
}

float Rational::toFloat() const {
	return (float)this->numerator/this->denominator;
}

void Rational::simplify() {
	int gcd_v = gcd(numerator,denominator);	
	numerator  = (int)numerator/gcd_v;
	denominator = (int)denominator/gcd_v;
}

int Rational::gcd(int a, int b) {
	int toReturn = 0;
	try {
		toReturn = mapsum(intersect(factorize(a),factorize(b)));
	} catch (std::exception& ex) {
		toReturn = 1;
	}
	return toReturn;
}

int Rational::lcm(int a, int b) {
	int toReturn = 0;
	try {
		toReturn = mapsum(unionof(factorize(a),factorize(b)));
	} catch (std::exception& ex) {
		toReturn = (a>b?a:b);	
	}
	return toReturn;
}

int Rational::mapsum(std::map<int,int> m) {
	int sum = 1;
	for (auto it : m) {
		sum *= (it.first * it.second);
	}
	return sum;
}

std::map<int,int> Rational::factorize(int num) {
	std::map<int,int> toReturn;
	//#stolen
	if (num == 1) {
		throw numberone_exception();
	}
	if (num < 0) {
		num *= -1;
	}
	int prim,i,j;
    if (num!=0){  //ha nem 0, akkor lefut
        while (num != 1){  // amíg a szám egy nem lesz
             prim = 1;
             i = 2;  // ebből képezzük a prímeket
             while(num % i != 0){  // ha osztható a legkisebb prímmel
                 i++;
                 j=2;
                 while(j<i && prim == 1){  // prímszámeldöntés
                     if (i % j == 0)
                         prim = 0;
                     j++;
                 }
             }
             num /= i;  // szám osztása az előállított prímszámmal
			 toReturn[i]++;
        }
    } 
	return toReturn;
}

std::map<int,int> Rational::unionof(const std::map<int,int>& s1, const std::map<int,int>& s2) {
	std::map<int,int> toReturn;
	for (auto it : s1) {
		toReturn[it.first] = it.second;
	}
	for (auto it : s2) {
		if (toReturn.find(it.first) == toReturn.end()) {
			toReturn[it.first] = it.second;
		} else if (toReturn[it.first] < it.second) {
			toReturn[it.first] = it.second;
		}
	}
	return toReturn;
}

std::map<int,int> Rational::intersect(const std::map<int,int>& s1, const std::map<int,int>& s2) {
	std::map<int,int> toReturn;
	for (auto it : s1) {
		auto pos = s2.find(it.first); 
		if (pos != s2.end()) {
			toReturn[it.first] = (it.second < pos->second ? pos->second : it.second);
		}
	}
	return toReturn;
}

std::ostream& operator <<(std::ostream& stream, const Rational& toDisp) {
	stream << toDisp.numerator;
	if (toDisp.denominator != 1)
		stream << "/" << toDisp.denominator;
	return stream;
}

Rational Rational::operator =(Rational other) {
	if (this != &other) {
		this->numerator = other.numerator;
		this->denominator = other.denominator;
	}
	return *this;
}
