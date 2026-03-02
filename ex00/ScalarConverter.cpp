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

void ScalarConverter::convert(const std::string& s) {
	ScalarConverter::LiteralType type = ScalarConverter::detectType(s);
	std::cout << type << std::endl;
	// switch (type) {
	// 	case CHAR:
	// 		convertChar(s);
	// 		break;
	// 	case INT:
	// 		convertInt(s);
	// 		break;
	// 	case FLOAT:
	// 		convertFloat(s);
	// 		break;
	// 	case DOUBLE:
	// 		convertDouble(s);
	// 		break;
	// }
}