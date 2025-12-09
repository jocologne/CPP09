
#include "PmergeMe.hpp"

static bool isValidNumber(const std::string& str) {
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]))
			return false;
	}
	char* end;
	long num = strtol(str.c_str(), &end, 10);
	if (num > INT_MAX || num < 0)
		return false;
	return true;
}

static double getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

static void display(const std::string& label, const std::vector<int>& container) {
	std::cout << label;
	for (size_t i = 0; i < container.size(); i++) {
		std::cout << container[i];
		if (i < container.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

//Vector Sorting

//Ortodox Canonical
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

//Public
void PmergeMe::parseInput(int ac, char** av) {
	if (ac < 2){
		throw std::invalid_argument("Error: no arguments");
	}
	for (int i = 1; i < ac; i++) {
		std::string arg = av[i];
		if (!isValidNumber(arg)) {
			throw std::invalid_argument("Error: invalid input");
		}
		int num = atoi(arg.c_str());
		_vector.push_back(num);
		_deque.push_back(num); 
	}
}

void PmergeMe::sortAndDisplay() {
	display("Before: ", _vector);
	//Vector sort
	double startVector = getTime();
	if (_vector.size() > 0) {
		//mergeInsertSortVector(_vector, 0, _vector.size() - 1);
	}
	double endVector = getTime();
	double timeVector = endVector - startVector;
	//Deque sort
	double startDeque = getTime();
	if (_deque.size() > 0) {
		//mergeInsertSortDeque(_deque, 0, _deque.size() -1);
	}
	double endDeque = getTime();
	double timeDeque = endDeque - startDeque;
	display("After: ", _vector);
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << timeVector << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::vector: " << timeDeque << " us" << std::endl;
}