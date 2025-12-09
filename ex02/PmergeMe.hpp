
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include	<string>
#include <sstream>
#include <exception>
#include <sys/time.h>
#include <climits>
#include <cstdlib>
#include <algorithm>

class PmergeMe {
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	//
	void parseInput(int ac, char** av);
	void sortAndDisplay();
};

#endif