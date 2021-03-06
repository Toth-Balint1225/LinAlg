#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <exception>
#include <algorithm>
#include <cmath>
#include "stringhandler.h"
#include <list>

class Rational {
private:
	int numerator, denominator;
private:
	class numberone_exception : public std::exception {
	public:
		const char* what() const noexcept override {
			return "Number 1 not factorizible";
		}
	};
private:
	int gcd(int a, int b) const;  // the greatest common denominator
	int lcm(int a, int b) const;  // ghe littlest common multiplier
	int mapsum(std::map<int,int> m) const;
	std::map<int,int> factorize(int num) const;
	std::map<int,int> unionof(const std::map<int,int>& s1, const std::map<int,int>& s2) const;
	std::map<int,int> intersect(const std::map<int,int>& s1, const std::map<int,int>& s2) const;
public:
	Rational();
	Rational(int _numerator, int _denominator);
	Rational(const Rational& other);
	Rational(const std::string& str);
	~Rational();

	void setInteractive();

	static Rational null();
	static Rational unit();

	// basic operations
	Rational addTo(const Rational& other) const;
	Rational subtract(const Rational& other) const;
	Rational negate() const;
	Rational invert() const;
	Rational multiplyBy(const Rational& other) const;
	Rational divideBy(const Rational& other) const;

	float toFloat() const;
	void simplify();

	//operators
	Rational operator +(const Rational& other) const;
	Rational operator -(const Rational& other) const;
	Rational operator *(const Rational& other) const;
	Rational operator /(const Rational& other) const;
	Rational operator =(const Rational& other);

	bool operator <=(const Rational& other) const;
	bool operator ==(const Rational& other) const;

	Rational power(unsigned e) const;

	friend std::ostream& operator <<(std::ostream& stream, const Rational& toDisp);
	std::string toFileFormat() const;
};

std::ostream& operator <<(std::ostream& stream, const Rational& toDisp);
#endif //RATIONAL_H
