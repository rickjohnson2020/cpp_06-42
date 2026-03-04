#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <iomanip>

class ScalarConverter {
private:
	enum LiteralType {
		CHAR, // '1', b
		INT, // -42, 0, 42
		FLOAT, // 42.0f
		DOUBLE, // 42.0
		INVALID
	};

	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);

	static LiteralType detectType(const std::string& s);
	static LiteralType detectNumType(const std::string& s);
	static char convertToChar(const std::string& s);
	static int convertToInt(const std::string& s);
	static float convertToFloat(const std::string& s);
	static double convertToDouble(const std::string& s);
	static void printAll(char c);
	static void printAll(int i);
	static void printAll(float f);
	static void printAll(double d);

	static void printCharFromDouble(double d);
	static void printIntFromDouble(double d);
	static void printFloat(float f);
	static void printDouble(double d);
	static bool isDisplayable(char c);

public:
	static void convert(const std::string& s);
};

#endif