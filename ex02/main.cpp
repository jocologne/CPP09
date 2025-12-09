
#include "PmergeMe.hpp"

int main(int ac, char** av) {
	try {
		PmergeMe sort;
		sort.parseInput(ac, av);
		sort.sortAndDisplay();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}