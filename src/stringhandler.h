#include <string>
#include <sstream>
#include <list>
#include <algorithm>

#include <exception>

#include <iostream>
#include <string>

#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

/* multitool facade created to easily handle standard strings */
// author Tóth Bálint
// 2020

class String {
private:
	//private constructor
	String() {}
private:
	// implementations
	
	template<typename T>
	T impl_strToNumericConversion(std::string str) const {
		T ret = 0;
		std::stringstream ss(str);
		ss >> ret;
		return ret;
	}

	template<typename T>
	std::string impl_numericToStrConversion(T number) const {
		std::string ret = "";
		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	template <class T>
    T impl_split(const std::string& str, char separator) const {
        T words;
        std::string word = "";
        for (auto c : str) {
            if (c != separator)
                word+=c;
            else {
                words.push_back(word);
                word = "";
            }
        }
        words.push_back(word);
        return words;
	}

	std::string impl_trim(std::string str) const {
		return str;
	}

public:
	// public functions
	String(const String&) = delete;

	static String& get() {
		static String instance;
		return instance;
	}

	// conversion functions

	// string to numeric:
	// waits for string representation of a number and a type
	// returns the number in the specified type
	// returns 0 if the conversion is invalid
	// example call: float f = String::strToNum<float>("3.14"); -> 3.14f
	template<typename T>  // the result type in template argument
	static T strToNum(std::string str) { 
		return get().impl_strToNumericConversion<T>(str);
	}

	// numeric to string 
	// waits for a type and a number of that type
	// returns the string representation of the number
	// returns "" if the conversion is invalid
	// example call: std::string s = numToStr<int>(3); -> "3"
	template<typename T>
	static std::string numToStr(T number) {
		return get().impl_numericToStrConversion<T>(number);
	}

	// utility functions

	// split:
	// waits for a string and a separator character (optional, by default it's [SPACE])
	// also waits for a return type template parameter (optional by default it's std::list)
	// all data structures could be parameters, that have a push_back() function
	// returns the string splitted into substrings (separator characters not included)
	template <class T = std::list<std::string>>
    static T split(const std::string& str, char separator = ' ') {
		return get().impl_split<T>(str,separator);
	}

	static std::string trim(std::string str) {
		return get().impl_trim(str);
	}


};



#endif //STRINGHANDLER_H
