#ifndef REPLUI_H
#define REPLUI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "stringhandler.h"
#include <list>
#include <map>
#include <vector>
#include "transformer.h"
#include "simpleio.h"
#include "rational.h"

/*
 * SYNTAX:
 * declare <var_type> <var_name>  // ex: declare matrix m1
 * init <var_type> <var_name> [= <value_name>] [$ <expression>] 
 * set <var_name> [= <value_name>] [$ <expression>]
 * eval <var_name> (*)(/)(-)(+) <var_name>  // ex: m1 + m2
 * transform <matrix_name>
 * invert <var_name>
 * negate <var_name>
 * null <type> [matrix -> size]
 * unit <type> [matrix -> size]
 * adj <matrix_name>
 * transpose <matrix_name>
 * import <var_name>
 * export <var_name>
 * list
 * delete <var_name>
 * print <var_name>
 *
 * EMBEDDED OPERATIONS
 * '$' evaluates next string substitutes to the previous
*/

/*
 * method:
 * input -> line : string -> operation type -> tokenize
 * declare matrix m1 -> declare operation -> type:matrix name:m1 -> m1.setInteractive()
 * init matrix m2 = m1 -> init operation -> mype:matrix sep:= name:m2 from:m1 -> m2=m1
 * init matrix m1i $ invert m1
 * -> init operation type:matrix name:m1i sep:$
 *  -> invert m1 = m1.invert() -> from:m1.invert()
 * -> m1i = m1.invert()
*/
template <class T>
class ReplUI {
private:
	std::map<std::string,T> consts;
	std::map<std::string,Matrix<T>> var;
	std::list<std::string> tokens = {"=","$","*","/","+","-"};
private:
//  std::list<std::string> tokenize() {
//  }
private:
	void printHelp() {
		std::cout << "* SYNTAX: " << std::endl;
		std::cout << "* declare <var_type> <var_name>  " << std::endl;
		std::cout << "* init <var_type> <var_name> [= <value_name>] [$ <expression>] " << std::endl;
		std::cout << "* set <var_name> [= <value_name>] [$ <expression>]" << std::endl;
		std::cout << "* eval <var_name> (*)(/)(-)(+) <var_name>" << std::endl;
		std::cout << "* transform <matrix_name>" << std::endl;
		std::cout << "* invert <var_name>" << std::endl;
		std::cout << "* negate <var_name>" << std::endl;
		std::cout << "* null <type> [matrix -> size]" << std::endl;
		std::cout << "* unit <type> [matrix -> size]" << std::endl;
		std::cout << "* adj <matrix_name>" << std::endl;
		std::cout << "* transpose <matrix_name>" << std::endl;
		std::cout << "* import <var_name>" << std::endl;
		std::cout << "* export <var_name>" << std::endl;
		std::cout << "* list" << std::endl;
		std::cout << "* delete <var_name>" << std::endl;
		std::cout << "* print <var_name>" << std::endl;
		std::cout << "* help" << std::endl;
		std::cout << "* quit" << std::endl;
	}

	void declare(const std::string& type, const std::string& name) {
		if (type.compare("matrix") == 0) {
			std::cout << "declaring " << name << " : " << type << std::endl;
			Matrix<T> m(1,1);
			m.setInteractive();
			var.insert(std::pair<std::string,Matrix<T>>(name,m));
		} else if (type.compare("scalar") == 0) {
			T s;
			s.setInteractive();
			consts.insert(std::pair<std::string,T>(name,s));
		} 	
	}

	void print(const std::string& name) {
		if (var.find(name) != var.end()) {
			std::cout << var[name] << std::endl;
		} else if (consts.find(name) != consts.end()) {
			std::cout << consts[name] << std::endl;
		} else {
			std::cout << "Invalid argument. " << name << " does not exist." << std::endl;
		}
		
	}

	void transform(const std::string& name) {
		auto m = var.find(name);
		if (m != var.end()) {
			SimpleIO io;
			Transformer<T> trafo = 
				Transformer<Rational>::TransformerBuilder<T>(m->second)
				.setInteractive(&io)
				.setVerbose(&std::cout)
				.build();
			trafo.transform();

		} else {
			std::cout << "Invalid argument. " << name << " is not a matrix or it does not exist." << std::endl;
		}
	}

	void export_variable(const std::string& name) {
		auto m = var.find(name);
		if (m != var.end()) {
			m->second.exportToFile(name+".lab");
		} else {
			std::cout << "Invalid argument. " << name << " is not a matrix or it does not exist." << std::endl;
		}
	}

	void import_variable(const std::string& name) {
		Matrix<T> m(1,1);
		m.importFromFile(name+".lab");
		var.insert(std::pair<std::string,Matrix<T>>(name,m));
	}

	void init(const std::string& type, const std::string& name, const std::string& expr) {
		if (type.compare("matrix") == 0) {
			
		}
	}

public:
	ReplUI() {
	}

	bool parseInput(const std::string& input) {
		std::vector<std::string> words = String::split<std::vector<std::string>>(input,' ');
		std::string operation = words.front();
		if (operation.compare("help") == 0) {
			printHelp();
		} else if (operation.compare("quit") == 0) {
			return false;
		} else if (operation.compare("declare") == 0) {
			declare(words.at(1),words.at(2));	
		} else if (operation.compare("print") == 0) {
			print(words.at(1));
		} else if (operation.compare("transform") == 0) {
			transform(words.at(1));
		} else if (operation.compare("export") == 0) {
			export_variable(words.at(1));
		} else if (operation.compare("import") == 0) {
			import_variable(words.at(1));
		}
		return true;
	}

	void start() {
		std::cout << "start" << std::endl;
		bool active = true;
		while (active) {
			active = update();
		}
		std::cout << "terminated" << std::endl;
	}

	bool update() {
		std::string input;
		// display prompt
		std::cout << ">";
		// read input
		std::getline(std::cin, input);
		// print output
		std::cout << std::flush;
		bool result = parseInput(input);
		return result;
	}

	~ReplUI() = default;
};

#endif //REPLUI_H
