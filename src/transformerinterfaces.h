#ifndef TRANSFORMERINTERFACES_H
#define TRANSFORMERINTERFACES_H

#include "matrix.h"
class TransformerIO {
public:
	virtual ~TransformerIO() = default;
	virtual std::pair<unsigned, unsigned> getGen() const = 0;
	virtual bool isFinished() const = 0;
};


template <class T = Real>
class Optimizer {
public:
	virtual ~Optimizer() = default;
	virtual std::pair<unsigned,unsigned> getGen(const Matrix<T>& state) const = 0;
	virtual bool isFinished(const Matrix<T>& state) const = 0;
};

#endif //TRANSFORMERINTERFACES_H
