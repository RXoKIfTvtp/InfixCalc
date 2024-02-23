
#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <cctype> // tolower()

/**
 * @class Util
 * @file Util.h
 * @brief A class to store extra functionallity
**/
class Util {
public:

	/**
	 * @brief Changes the case of all the characters in the string to lowercase
	 * @param s The string to change
	 * @return The lowercase string
	**/
	static std::string &toLowerCase(std::string &s);
};

#endif /* STRING_UTIL_H */

