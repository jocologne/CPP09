
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>

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
	void displayBefore();
	void displayAfter();
};

#endif