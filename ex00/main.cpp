
#include <iostream>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Usage: " << av[0] << " <filename>" << std::endl;
		return 1;
	}
	return 0;
}