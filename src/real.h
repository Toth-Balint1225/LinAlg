#ifndef REAL_H
#define REAL_H

#include <ostream>

// a wrapper class for double
class Real {
private:
	double value = 0.0f;
public:
	Real();
	Real(double _value);
	~Real();

	static Real null();
	static Real unit();

	Real negate() const;
	Real invert() const;

	Real operator +(const Real& other) const;
	Real operator -(const Real& other) const;
	Real operator *(const Real& other) const;
	Real operator /(const Real& other) const;
	Real operator =(const Real& other);

	bool operator <=(const Real& other) const;

	Real power(unsigned e) const;

	friend std::ostream& operator <<(std::ostream& stream, const Real& r);
};

std::ostream& operator <<(std::ostream& stream, const Real& r);

#endif //REAL_H
