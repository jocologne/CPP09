
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

static std::vector<size_t> jacobSequence(size_t n) {
	std::vector<size_t> seq;
	size_t j_prev = 1;
	size_t j_curr = 1;
	while (j_curr < n) {
		seq.push_back(j_curr);
		size_t next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = next;
	}
	return seq;
}

//Vector sorting
static void binaryInsertVector(std::vector<int>& v, int value, size_t high) {
	size_t low = 0;
	while (low < high) {
		size_t mid = (low + high) / 2;
		if (value < v[mid])
			high = mid;
		else 
			low = mid + 1;
	}
	v.insert(v.begin() + low, value);
}

static void fordJohnsonVector(std::vector<int>& v) {
	size_t n = v.size();
	if (n <= 1)
		return;
	if (n == 2 && v[0] > v[1]) {
		std::swap(v[0], v[1]);
		return;
	}
	std::vector<int> big;
	std::vector<int> small;
	big.reserve(n);
	small.reserve(n);
	for (size_t i = 0; i + 1 < n; i += 2) {
		int a = v[i];
		int b = v[i + 1];
		if (a > b) {
			big.push_back(a);
			small.push_back(b);
		} else {
			big.push_back(b);
			small.push_back(a);
		}
	}
	bool hasOdd = (n % 2 == 1);
	int oddValue = hasOdd ? v[n - 1] : 0;
	fordJohnsonVector(big);
	std::vector<size_t> jacob = jacobSequence(small.size());
	std::vector<bool> used(small.size(), false);
	for (size_t k = 0; k < jacob.size(); k++) {
		size_t idx = jacob[k] - 1;
		if (idx < small.size() && !used[idx]) {
			binaryInsertVector(big, small[idx], big.size());
			used[idx] = true;
		}
	}
	for (size_t i = 0; i < small.size(); i++) {
		if (!used[i]) {
			binaryInsertVector(big, small[i], big.size());
		}
	}
	if (hasOdd) {
		binaryInsertVector(big, oddValue, big.size());
	}
	v = big;
}

//Deque sorting
static void binaryInsertDeque(std::deque<int>& d, int value, size_t high) {
	size_t low = 0;
	while (low < high) {
		size_t mid = (low + high) / 2;
		if (value < d[mid])
			high = mid;
		else
			low = mid + 1;
	}
	d.insert(d.begin() + low, value);
}

static void fordJohnsonDeque(std::deque<int>& d) {
	size_t n = d.size();
	if (n <= 1)
		return;
	if (n == 2 && d[0] > d[1]) {
		std::swap(d[0], d[1]);
		return;
	}
	std::deque<int> big;
	std::deque<int> small;
	for (size_t i = 0; i + 1 < n; i += 2) {
		int a = d[i];
		int b = d[i + 1];
		if (a > b) {
			big.push_back(a);
			small.push_back(b);
		} else {
			big.push_back(b);
			small.push_back(a);
		}
	}
	bool odd = (n % 2 == 1);
	int lastOdd = odd ? d[n - 1] : 0;
	fordJohnsonDeque(big);
	std::vector<size_t> jacob = jacobSequence(small.size());
	std::vector<bool> used(small.size(), false);
	for (size_t j = 0; j < jacob.size(); j++) {
		size_t idx = jacob[j];
		if (idx < small.size()) {
			binaryInsertDeque(big, small[idx], big.size());
			used[idx] = true;
		}
	}
	for (size_t i = 0; i < small.size(); i++) {
		if (!used[i])
			binaryInsertDeque(big, small[i], big.size());
	}
	if (odd)
		binaryInsertDeque(big, lastOdd, big.size());
	d = big;
}

//Ortodox Canonical
PmergeMe::PmergeMe() : _parseTime(0) {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vector = other._vector;
		_deque = other._deque;
		_parseTime = other._parseTime;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

//Public
void PmergeMe::parseInput(int ac, char** av) {
	if (ac < 2){
		throw std::invalid_argument("Error: no arguments");
	}
	double parseStart = getTime();
	for (int i = 1; i < ac; i++) {
		std::string arg = av[i];
		if (!isValidNumber(arg)) {
			throw std::invalid_argument("Error: invalid input");
		}
		int num = atoi(arg.c_str());
		_vector.push_back(num);
		_deque.push_back(num); 
	}
	double parseEnd = getTime();
	_parseTime = parseEnd - parseStart;
}

void PmergeMe::sortAndDisplay() {
	display("Before: ", _vector);
	//Vector sort
	double startVector = getTime();
	if (_vector.size() > 0) {
		fordJohnsonVector(_vector);
	}
	double endVector = getTime();
	double timeVector = endVector - startVector;
	//Deque sort
	double startDeque = getTime();
	if (_deque.size() > 0) {
		fordJohnsonDeque(_deque);
	}
	double endDeque = getTime();
	double timeDeque = endDeque - startDeque;
	display("After: ", _vector);
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << timeVector + _parseTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: " << timeDeque + _parseTime << " us" << std::endl;
}