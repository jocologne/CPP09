
#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Usage: " << av[0] << " <filename>" << std::endl;
		return 1;
	}
	try {
		BitcoinExchange btc;
		btc.loadExchangeRates("data.csv");
		btc.processInput(av[1]);
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} 
	return 0;
}