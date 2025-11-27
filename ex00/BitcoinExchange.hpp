
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, float> _exchangeRates;
    bool isValidDate(const std::string &date) const;
    bool isValidValue(const std::string &value) const;
    float getRate(const std::string &date) const;
public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);

    void loadExchangeRates(const std::string &filename);
    void processInput(const std::string &filename) const;
};

#endif	