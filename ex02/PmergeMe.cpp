
#include "PmergeMe.hpp"

static bool isValidNumber(const std::string& str) {
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]))
			return false;
	}
	char* end;
	long num = strtol(str.c_str(), end&, 10);
	if (num > INT_MAX || num < 0)
		return false;
	return true;
}

static double getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv_tv_usec);
}

