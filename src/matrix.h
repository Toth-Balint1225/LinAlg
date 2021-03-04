#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <exception>
#include <string>
#include <sstream>

// matrix: A_ij
// j=   1   2   3   4
// i= 1|a11 a12 a13 a14| 
//    2|a21 a22 a23 a24|
//    3|a31 a32 a33 a34|

class invalid_size_exception : public std::exception {
private:
	int m1h, m1w, m2h, m2w;
	std::string type;
public:
	invalid_size_exception(int _m1h, int _m1w, int _m2h, int _m2w, const std::string& _type):
		m1h(_m1h), m1w(_m1w), m2h(_m2h), m2w(_m2w), type(_type) {
	}
	~invalid_size_exception() override = default;
	const char* what() const noexcept override {
		std::stringstream ss;
		ss << "CANNOT "<< type << " matrix [" << m1h << ";" << m1w << "]"
		   << " to " <<" matrix [" << m2h << ";" << m2w << "]";
		return ss.str().c_str();
	}
};

template <class T = float>
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

	Matrix<T> add(Matrix<T>& m2) {
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


	Matrix<T> multiply(Matrix<T>& m2) {
		if (this->height != m2.height || this->width != m2.width)
			throw invalid_size_exception(
					this->height, this->width, m2.height, m2.width, "multiply");
		Matrix<T> result(this->height,this->width);
		return result;
	}
};

template <class T=float>
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

template <class T = float>
Matrix<T> multiplyByScalar(const T& s, const Matrix<T>& m) {
	Matrix<T> result(m.getHeight(), m.getWidth());
	for (unsigned i=0;i<m.getHeight();i++) {
		for (unsigned j=0;j<m.getWidth();j++) {
			result.setElement(i,j,s*m.getElement(i,j));
		}
	}
	return result;
}

#endif //MATRIX_H
