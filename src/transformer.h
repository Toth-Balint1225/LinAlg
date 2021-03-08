#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "matrix.h"
#include "real.h"
#include <exception>
#include <string>
#include <sstream>
#include <ostream>

/*
 * linear transformation algorithm
 * always need:
 * 	matrix of column vectors
 * optionals:
 * 	base | canonical base
 *	interactive [I/O] | automatic [optimizer]
 *
*/

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

class invalid_generator : public std::exception {
private:
	std::string msg;
public:
	invalid_generator(unsigned r, unsigned c) {
		std::stringstream ss;
		ss << "Invalid generator: ("  << r << ";" << c << ")";
		msg = ss.str();
	}
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

template <class T = Real>
class Transformer {
public:
	template <class Type = Real>
	class TransformerBuilder {
	private:
		Matrix<Type> model;
		bool interactive = false;
		bool verbose = false;
		std::ostream* verboseOutput = nullptr;
		TransformerIO* io = nullptr;
		Optimizer<T>* opt = nullptr;
		friend class Transformer;
	public:
		TransformerBuilder(const Matrix<Type>& _model) :
			model(_model) {
		}
		TransformerBuilder<Type>& setInteractive(TransformerIO* _io) {
			this->interactive = true;
			this->io = _io;
			return *this;
		}

		TransformerBuilder<Type>& setOptimized(Optimizer<Type>* _opt) {
			this->opt = _opt;
			return *this;
		}

		TransformerBuilder<Type>& setVerbose(std::ostream* _verboseOutput = &std::cout) {
			this->verbose = true;
			this->verboseOutput = _verboseOutput;
			return *this;
		}

		Transformer<Type> build() {
			return Transformer(*this);
		}
	};

private:
	Matrix<T> model;
	bool interactive;
	bool verbose;
	std::ostream* verboseOutput = nullptr;
	TransformerIO* io;
	Optimizer<T>* opt;
public:
	Transformer(const TransformerBuilder<T>& builder):
		model(builder.model), 
		interactive(builder.interactive),
		verbose(builder.verbose),
		verboseOutput(builder.verboseOutput),
		io(builder.io),
		opt(builder.opt) {
	}
	~Transformer() {
	}
	const Matrix<T>& getModel() const {
		return model;
	}
	Matrix<T> step(Matrix<T>& state, unsigned genRow, unsigned genCol) const {
		if (state.getElement(genRow,genCol) == T::null()) {
			throw invalid_generator(genRow,genCol);
		}
		Matrix<T> next(state.getHeight(), state.getWidth());
		T generator = state.getElement(genRow,genCol);	
		// generator row
		for (unsigned j=0;j<state.getWidth();j++) {
			next.setElement(genRow,j,state.getElement(genRow,j)/generator);
		}
		// generator column
		for (unsigned i=0;i<state.getHeight();i++) {
			if (i != genRow)
				next.setElement(i,genCol,T::null());
		}
		for (unsigned i=0;i<state.getHeight();i++) {
			if (i != genRow) {
				for (unsigned j=0;j<state.getWidth();j++) {
					if (j != genCol) {
						int rowDiff = i-genRow;
						int colDiff = j-genCol;
						next.setElement(i,j,state.getElement(i,j)-(state.getElement(i-rowDiff,j)*state.getElement(i,j-colDiff))/generator);
					}
				}
			}
		}
		return next;
	}
	
	void displayVerbose(unsigned row, unsigned col, const Matrix<T>& transformed) const {
		*verboseOutput << "(" << row << ";" << col << ")" << std::endl;
		*verboseOutput << transformed << std::endl;
	}

	Matrix<T> transform() const {
		Matrix<T> transformed = model;
		if (verbose) {
			displayVerbose(0,0,transformed);
		}
		while (false || (opt?(!opt->isFinished(model)):false) || (io?(!io->isFinished()):false)) {
			unsigned genRow=0, genCol=0;
			if (io) {
				std::pair<unsigned,unsigned> generator = io->getGen();
				genRow = generator.first;
				genCol = generator.second;
			}
			if (opt) {
				std::pair<unsigned,unsigned> generator = opt->getGen(model);
				genRow = generator.first;
				genCol = generator.second;
			}
			try {
				transformed = step(transformed,genRow,genCol);
			} catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			if (verbose) {
				displayVerbose(genRow, genCol, transformed);
			}
		}
		return transformed;
	}
};

#endif //TRANSFORMER_H
