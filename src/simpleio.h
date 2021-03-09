#ifndef SIMPLEIO_H_
#define SIMPLEIO_H_

#include <iostream>
#include "transformer.h"

class SimpleIO : public TransformerIO {
public:
	virtual ~SimpleIO() override = default; 
	std::pair<unsigned, unsigned> getGen() const override {
		unsigned row, col;
		std::cout << "generator row: ";
		std::cin >> row;
		std::cout << "generator column: ";
		std::cin >> col;
		return std::pair<unsigned,unsigned>(row,col);
	}
	virtual bool isFinished() const override {
		bool result = false;
		std::cout << "Finished? [1/0] : ";
		std::cin >> result;
		return result;
	}
};

#endif //SIMPLEIO_H_
