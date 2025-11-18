
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange
{
private:
    std::map<std::string, float> exchangeRates;
public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);

    void loadExchangeRates(const std::string &filename);
    float getExchangeRate(const std::string &date) const;
    void printExchangeRates() const;
};

#endif	