#include "./ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	*this = other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& s) {
	if (s.empty())
		return INVALID;
	if (s == "nanf" || s == "+inff" || s == "-inff")
		return FLOAT;
	if (s == "nan" || s == "+inf" || s == "-inf")
		return DOUBLE;
	if ((s.length() == 3 && s[0] == '\'' && s[2] == '\'')
			|| (s.length() == 1 && !std::isdigit(s[0])))
		return CHAR;
	return ScalarConverter::detectNumType(s);
}

ScalarConverter::LiteralType ScalarConverter::detectNumType(const std::string& s) {
	size_t i = 0;

	if (s[i] == '-' || s[i] == '+') {
		i++;
		if (!s[i])
			return INVALID;
	}

	int digitCount = 0;
	int dotCount = 0;
	int fCount = 0;
	for (; i < s.length(); i++) {
		if (std::isdigit(s[i])) {
			digitCount++;
			continue;
		}
		if (s[i] == '.') {
			dotCount++;
			if (dotCount > 1)
				return INVALID;
			continue;
		}
		if (s[i] == 'f') {
			if (i != s.length() - 1)
				return INVALID;
			fCount++;
			if (fCount > 1)
				return INVALID;
			continue;
		}
		return INVALID;
	}

	if (digitCount == 0)
		return INVALID;
	if (dotCount == 0 && fCount == 0)
		return INT;
	if (dotCount == 1 && fCount == 0)
		return DOUBLE;
	if (dotCount == 1 && fCount == 1)
		return FLOAT;
	return INVALID;
}

char ScalarConverter::convertToChar(const std::string& s) {
	if (s.size() == 3 && s[0] == '\'' && s[2] == '\'')
		return s[1];
	return s[0];
}

int ScalarConverter::convertToInt(const std::string& s) {
	double d = std::atof(s.c_str());
	double minI = static_cast<double>(std::numeric_limits<int>::min());
	double maxI = static_cast<double>(std::numeric_limits<int>::max());
	if (d < minI || d > maxI)
		throw std::out_of_range("int overflow");
	return static_cast<int>(d);
}

float ScalarConverter::convertToFloat(const std::string& s) {
	double d = std::atof(s.c_str());
	return static_cast<float>(d);
}

double ScalarConverter::convertToDouble(const std::string& s) {
	return std::atof(s.c_str());
}

bool ScalarConverter::isDisplayable(char c) {
	unsigned char uc = static_cast<unsigned char>(c);
	return (uc >= 32 && uc <= 126);
}

void ScalarConverter::printAll(char c) {
	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);

	std::cout << "char: ";
	if (!isDisplayable(c))
		std::cout << "Non displayable" << std::endl;
	std::cout << "'" << c << "'" << std::endl;
	std::cout << "int: " << i << std::endl;
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printAll(int i) {
	double d = static_cast<double>(i);
	float f = static_cast<float>(i);

	printCharFromDouble(d);
	std::cout << "int: " << i << std::endl;
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printAll(float f) {
	double d = static_cast<double>(f);

	printCharFromDouble(d);
	printIntFromDouble(d);
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printAll(double d) {
	printCharFromDouble(d);
	printIntFromDouble(d);
	printFloat(static_cast<float>(d));
	printDouble(d);
}

void ScalarConverter::printCharFromDouble(double d) {
	std::cout << "char: ";
	if (std::isnan(d) || std::isinf(d)) {
		std::cout << "impossible" << std::endl;
		return;
	}
	double minC = static_cast<double>(std::numeric_limits<char>::min());
	double maxC = static_cast<double>(std::numeric_limits<char>::max());
	if (d < minC || d > maxC) {
		std::cout << "impossible" << std::endl;
		return;
	}
	char c = static_cast<char>(d);
	if (!isDisplayable(c)) {
		std::cout << "Non displayable" << std::endl;
		return;
	}
	std::cout << "'" << c << "'" << std::endl;
}

void ScalarConverter::printIntFromDouble(double d) {
	std::cout << "int: ";
	if (std::isnan(d) || std::isinf(d)) {
		std::cout << "impossible" << std::endl;
		return;
	}
	double minI = static_cast<double>(std::numeric_limits<int>::min());
	double maxI = static_cast<double>(std::numeric_limits<int>::max());
	if (d < minI || d > maxI) {
		std::cout << "impossible" << std::endl;
		return;
	}
	std::cout << static_cast<int>(d) << std::endl;
}

void ScalarConverter::printFloat(float f) {
	std::cout << "float: ";
	if (std::isnan(f)) {
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(f)) {
		std::cout << (f > 0 ? "+inff" : "-inff") << std::endl;
		return;
	}
	if (f == (int)f)
		std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	else
		std::cout << f << "f" << std::endl;
}

void ScalarConverter::printDouble(double d) {
	std::cout << "double: ";
	if (std::isnan(d)) {
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(d)) {
		std::cout << (d > 0 ? "+inf" : "-inf") << std::endl;
		return;
	}
	if (d == (int)d)
		std::cout << std::fixed << std::setprecision(1) << d << std::endl;
	else
		std::cout << d << std::endl;
}

void ScalarConverter::convert(const std::string& s) {
	LiteralType type = detectType(s);
	std::cout << "Type: " << type << std::endl;

	switch (type) {
		case INVALID: {
			std::cout << "Invalid input" << std::endl;
			break;
		}
		case CHAR: {
			char c = convertToChar(s);
			printAll(c);
			break;
		}
		case INT: {
			try {
				int i = convertToInt(s);
				printAll(i);
			} catch (const std::exception&) {
				double d = convertToDouble(s);
				printAll(d);
			}
			break;
		}
		case FLOAT: {
			float f = convertToFloat(s);
			printAll(f);
			break;
		}
		case DOUBLE: {
			double d = convertToDouble(s);
			printAll(d);
			break;
		}
	}
}