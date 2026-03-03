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
		return PSEUDO_DOUBLE;
	if (s == "nan" || s == "+inf" || s == "-inf")
		return PSEUDO_FLOAT;
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
		// TODO: mignt need extra check
		return DOUBLE;
	if (dotCount == 1 && fCount == 1)
		return FLOAT;
	return INVALID;
}

double ScalarConverter::parseToDouble(const std::string& s, LiteralType type) {
	if (type == CHAR) {
		if (s.size() == 3 && s[0] == '\'' && s[2] == '\'')
			return static_cast<double>(s[1]);
		return static_cast<double>(s[0]);
	} else {
		return std::atof(s.c_str());
	}
}

bool ScalarConverter::isPrintableAscii(char c) {
	unsigned char uc = static_cast<unsigned char>(c);
	return (uc >= 32 && uc <= 126);
}

void ScalarConverter::printChar(double d) {
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
	if (!isPrintableAscii(c)) {
		std::cout << "Non displayable" << std::endl;
		return;
	}
	std::cout << "'" << c << "'" << std::endl;
}

void ScalarConverter::printInt(double d) {
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

void ScalarConverter::printFloat(double d, LiteralType type) {
	std::cout << "float: ";
	if (std::isnan(d)) {
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(d)) {
		std::cout << (d > 0 ? "+inff" : "-inff") << std::endl;
		return;
	}
	float f = static_cast<float>(d);
	if (std::isinf(f)) {
		std::cout << (d > 0 ? "+inff" : "-inff") << std::endl;
		return;
	}
	//TODO:
}

void ScalarConverter::printDouble(double d, LiteralType type) {
	std::cout << "double: ";
	if (std::isnan(d)) {
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(d)) {
		std::cout << (d > 0 ? "+inff" : "-inff") << std::endl;
		return;
	}
	//TODO:
}

void ScalarConverter::convert(const std::string& s) {
	LiteralType type = detectType(s);
	std::cout << type << std::endl;
	double d = parseToDouble(s, type);
	std::cout << d << std::endl;

	switch (type) {
		case INVALID:
			std::cout << "Invalid input" << std::endl;
			break;
		case CHAR:
			printChar(d);
			break;
		case INT:
			printInt(d);
			break;
		case FLOAT:
			printFloat(d, type);
			break;
		case DOUBLE:
			printDouble(d, type);
			break;
	}
}