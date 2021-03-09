#ifndef TRANSFORMERBUILDER_H
#define TRANSFORMERBUILDER_H

#include "transformerinterfaces.h"
#include "transformer.h"
#include "matrix.h"

template <class T = Real>
class TransformerBuilder {
private:
	Matrix<T> model;
	bool interactive = false;
	bool verbose = false;
	std::ostream* verboseOutput = nullptr;
	TransformerIO* io = nullptr;
	Optimizer<T>* opt = nullptr;
	friend class Transformer<T>;
public:
	TransformerBuilder(const Matrix<T>& _model) :
		model(_model) {
	}
	TransformerBuilder<T>& setInteractive(TransformerIO* _io) {
		this->interactive = true;
		this->io = _io;
		return *this;
	}

	TransformerBuilder<T>& setOptimized(Optimizer<T>* _opt) {
		this->opt = _opt;
		return *this;
	}

	TransformerBuilder<T>& setVerbose(std::ostream* _verboseOutput = &std::cout) {
		this->verbose = true;
		this->verboseOutput = _verboseOutput;
		return *this;
	}

	Transformer<T> build() {
		return Transformer(*this);
	}
};

#endif //TRANSFORMERBUILDER_H
