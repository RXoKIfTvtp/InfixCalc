
#include "Util.h"

std::string &Util::toLowerCase(std::string &s) {
	int i;
	for (i = 0; i < (int)s.length(); i++) {
		s[i] = std::tolower(s[i]);
	}
	return s;
}

