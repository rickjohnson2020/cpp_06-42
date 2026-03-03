#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>

class ScalarConverter {
private:
	enum LiteralType {
		CHAR, // '1', b
		INT, // -42, 0, 42
		FLOAT, // 42.0f
		DOUBLE, // 42.0
		PSEUDO_FLOAT, // nanf, +inff, -inff
		PSEUDO_DOUBLE, // nan, +inf, -inf
		INVALID
	};

	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);

	static LiteralType detectType(const std::string& s);
	static LiteralType detectNumType(const std::string& s);
	static double parseToDouble(const std::string& s, LiteralType type);
	static void printChar(double d);
	static void printInt(double d);
	static void printFloat(double d, LiteralType type);
	static void printDouble(double d, LiteralType type);
	static bool isPrintableAscii(char c);

public:
	static void convert(const std::string& s);
};

#endif