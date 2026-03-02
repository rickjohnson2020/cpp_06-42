#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>

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

public:
	static void convert(const std::string& s);
};

#endif