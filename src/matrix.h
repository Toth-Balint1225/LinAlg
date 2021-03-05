#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <exception>
#include <string>
#include <sstream>

#include "real.h"

// matrix: A_ij
// j=   0   1   2   3  
// i= 0|a00 a01 a02 a03| 
//    1|a10 a11 a12 a13|
//    2|a20 a21 a22 a23|

class invalid_size_exception : public std::exception {
private:
	std::string msg;
public:
	invalid_size_exception(int m1h, int m1w, int m2h, int m2w, const std::string& type) {
		std::stringstream ss;
		ss << "ERROR cannot "<< type << " matrix [" << m1h << ";" << m1w << "]"
			<< " to " <<" matrix [" << m2h << ";" << m2w << "]";
		msg = ss.str();
	}
	~invalid_size_exception() override = default;
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

class not_square_exception : public std::exception {
private:
	std::string msg;
public:
	not_square_exception(int h,int w, const std::string& type) {
		std::stringstream ss;
		ss << "ERROR cannot calculate " << type << " of matrix ["
			<< h << ";" << w << "]";
		msg = ss.str();
	}
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

template <class T = Real>
class Matrix {
private:
	unsigned height = 0;
	unsigned width = 0;
	T** matrix = nullptr;
public:
	Matrix() = default;

	Matrix(unsigned _height, unsigned _width):
		height(_height), width(_width) {
		matrix = new T*[height];
		for (unsigned i=0;i<height;i++)
			matrix[i] = new T[width];
	}

	Matrix(const Matrix& other):
			height(other.height), width(other.width) {
		matrix = new T*[height];
		for (unsigned i=0;i<height;i++)
			matrix[i] = new T[width];
		for (unsigned i=0;i<height;i++) {
			for (unsigned j=0;j<width;j++) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	~Matrix() {
		for (unsigned i=0;i<height;i++)
			delete [] matrix[i];
		delete [] matrix;
	}

	unsigned getHeight() const {
		return height;
	}

	unsigned getWidth() const {
		return width;
	}

	void setElement(unsigned i, unsigned j,const T& data) {
		matrix[i][j] = data;
	}

	const T& getElement(unsigned i, unsigned j) const {
		return matrix[i][j];
	}

	T& getElement(unsigned i, unsigned j) {
		return matrix[i][j];
	}

	static Matrix<T> null(unsigned size) {
		Matrix<T> result(size,size);
		for (unsigned i=0;i<size;i++) {
			for (unsigned j=0;j<size;j++) {
				result.matrix[i][j] = T::null();
			}
		}
		return result;
	}

	static Matrix<T> unit(unsigned size) {
		Matrix<T> result(size,size);
		for (unsigned i=0;i<size;i++) {
			for (unsigned j=0;j<size;j++) {
				result.matrix[i][j] = (i==j?T::unit():T::null());
			}
		}
		return result;
	}

	Matrix<T> add(const Matrix<T>& m2) const {
		if (this->height != m2.height || this->width != m2.width)
			throw invalid_size_exception(
					this->height, this->width, m2.height, m2.width, "add");
		Matrix<T> result(this->height,this->width);
		for (unsigned i=0;i<result.height;i++) {
			for (unsigned j=0;j<result.width;j++) {
				result.matrix[i][j] = this->matrix[i][j] + m2.matrix[i][j];
			}
		}
		return result;
	}


	Matrix<T> multiply(const Matrix<T>& other) const {
		if (this->width != other.height)
			throw invalid_size_exception(
					this->height, this->width, other.height, other.width, "multiply");
		Matrix<T> result(this->height,other.width);
		for (unsigned i=0;i<this->height;i++) {
			for (unsigned k=0;k<other.width;k++) {
				T sum = T::null();
				for (unsigned j=0;j<this->width;j++) {
					sum = sum + (this->matrix[i][j]*other.matrix[j][k]);	
				}
				result.matrix[i][k] = sum;
			}
		}
		return result;
	}
	Matrix<T> operator +(const Matrix<T>& other) const {
		return add(other);
	}
	Matrix<T> operator -(const Matrix<T>& other) const {
		return add(multiplyByScalar(T::unit().negate(),other));
	}
	Matrix<T> operator *(const Matrix<T>& other) const {
		return multiply(other);
	}

	Matrix<T> operator =(const Matrix<T>& other) {
		if (this != &other) {
			for (unsigned i=0;i<height;i++)
				delete [] matrix[i];
			delete [] matrix;
			this->height = other.height;
			this->width = other.width;
			matrix = new T*[height];
			for (unsigned i=0;i<height;i++)
				matrix[i] = new T[width];
			for (unsigned i=0;i<height;i++) {
				for (unsigned j=0;j<width;j++) {
					this->matrix[i][j] = other.matrix[i][j];
				}
			}
		}
		return *this;
	}

	Matrix<T> submatrix(unsigned row, unsigned column) const {
		Matrix<T> result(height-1,width-1);
		unsigned rowCorrect = 0;
		for (unsigned i=0;i<this->height;i++) {
			if (i == row) {
				rowCorrect = 1;
			} else {
				unsigned colCorrect = 0;
				for (unsigned j=0;j<this->width;j++) {
					if (j == column) {
						colCorrect = 1;
					} else {
						result.matrix[i-rowCorrect][j-colCorrect] = 
							this->matrix[i][j];
					}
				}
			}
		}
		return result;
	}

	T det() const {
		if (height != width) {
			throw not_square_exception(height,width,"determinant");
		}
		if (this->height == 1) {
			return this->matrix[0][0];
		} else {
			T sum = T::null();
			for (unsigned column=0;column<this->width;column++) {
				sum = sum + T::unit().negate().power(column) * this->matrix[0][column] * this->submatrix(0,column).det();
			}
			return sum;
		}
	}

	Matrix<T> adj() const {
		if (height != width) {
			throw not_square_exception(height,width,"determinant");
		}
		Matrix<T> result(this->height, this->width);
		for (unsigned i=0;i<this->height;i++) {
			for (unsigned j=0;j<this->width;j++) {
				result.matrix[i][j] = T::unit().negate().power(i+j)*this->submatrix(j,i).det();
			}
		}
		return result;
	}

	Matrix<T> invert() const {
		if (height != width) {
			throw not_square_exception(height,width,"determinant");
		}
		Matrix<T> result(this->height, this->width);
		T coefficient = this->det().invert();
		result = coefficient * this->adj();
		return result;
	}


};

template <class T = Real>
std::ostream& operator <<(std::ostream& stream, const Matrix<T>& m) {
	for (unsigned i=0;i<m.getHeight();i++) {
		stream << "|";
		for (unsigned j=0;j<m.getWidth();j++) {
			stream << "\t" << m.getElement(i,j);
		}
		stream << "\t|";
		stream << std::endl;
	}
	return stream;
}

template <class T = Real>
Matrix<T> multiplyByScalar(const T& s, const Matrix<T>& m) {
	Matrix<T> result(m.getHeight(), m.getWidth());
	for (unsigned i=0;i<m.getHeight();i++) {
		for (unsigned j=0;j<m.getWidth();j++) {
			result.setElement(i,j,s*m.getElement(i,j));
		}
	}
	return result;
}

template <class T = Real>
Matrix<T> operator *(const T& s, const Matrix<T>& m) {
	return multiplyByScalar(s,m);
}

#endif //MATRIX_H
