#include "real.h"

Real::Real():
	value(0.0f){
}

Real::Real(double _value):
	value(_value) {
}

Real::~Real() {
}


Real Real::null() {
	return Real(0.0f);
}

Real Real::unit() {
	return Real(1.0f);
}

Real Real::operator +(const Real& other) const {
	return Real(this->value + other.value);
}

Real Real::operator -(const Real& other) const {
	return Real(this->value - other.value);
}

Real Real::operator *(const Real& other) const {
	return Real(this->value * other.value);
}

Real Real::operator /(const Real& other) const {
	return Real(this->value / other.value);
}

Real Real::operator =(const Real& other) {
	if (this != &other) {
		this->value = other.value;
	}
	return *this;
}

bool Real::operator <=(const Real& other) const {
	return this->value <= other.value;
}


std::ostream& operator <<(std::ostream& stream, const Real& r) {
	stream << r.value;
	return stream;
}
