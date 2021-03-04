#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>

// matrix: A_ij
// j=   1   2   3   4
// i= 1|a11 a12 a13 a14| 
//    2|a21 a22 a23 a24|
//    3|a31 a32 a33 a34|


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

#endif //MATRIX_H
