#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <map>
#include <exception>

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
	int gcd(int a, int b);  // the greatest common denominator
	int lcm(int a, int b);  // ghe littlest common multiplier
	int mapsum(std::map<int,int> m);
	std::map<int,int> factorize(int num);
	std::map<int,int> unionof(const std::map<int,int>& s1, const std::map<int,int>& s2);
	std::map<int,int> intersect(const std::map<int,int>& s1, const std::map<int,int>& s2);
public:
	Rational();
	Rational (int _numerator, int _denominator);
	Rational (const Rational& other);
	~Rational();

	// basic operations
	Rational addTo(Rational& other);
	Rational subtract(Rational& other);
	Rational negate();
	Rational invert();
	Rational multiplyBy(Rational& other);
	Rational divideBy(Rational& other);

	float toFloat() const;
	void simplify();

	//operators
	Rational operator +(Rational& other);
	Rational operator -(Rational& other);
	Rational operator *(Rational& other);
	Rational operator /(Rational& other);
	Rational operator =(Rational other);

	bool operator <=(const Rational& other);

	friend std::ostream& operator <<(std::ostream& stream, const Rational& toDisp);
};

std::ostream& operator <<(std::ostream& stream, const Rational& toDisp);
#endif //RATIONAL_H
