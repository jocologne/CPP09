
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
};

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if(this != &other) {
        this->_exchangeRates = other._exchangeRates;
    }
    return *this;
};

void BitcoinExchange::loadExchangeRates(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if(!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, priceStr;
        if (!std::getline(ss, date, ',') || !std::getline(ss, priceStr))
            continue;
        float price = std::strtof(priceStr.c_str(), NULL);
        _exchangeRates[date] = price;
    }
}

bool BitcoinExchange::isValidDate(const std::string &date) const {
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    int year = std::atoi(date.substr(0,4).c_str());
    int month = std::atoi(date.substr(5,2).c_str());
    int day = std::atoi(date.substr(8,2).c_str());
    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 0)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &value) const {
    bool dot = false;
    for (std::size_t i = 0; i < value.size(); ++i) {
        if(value[i] == '.') {
            if(dot)
                return false;
            dot = true;
        }
        else if (!std::isdigit(value[i]))
            return false;
    }
    return true;
}

float BitcoinExchange::getRate(const std::string &date) const {
    std::map<std::string, float>::const_iterator it = _exchangeRates.lower_bound(date);
    if(it != _exchangeRates.end() && it->first == date)
        return it->second;
    if(it == _exchangeRates.begin())
        throw std::runtime_error("No date found.");
    --it;
    return it->second;
}

void BitcoinExchange::processInput(const std::string &filename) const {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, sep);
        std::string valueStr = line.substr(sep + 1);
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (valueStr[0] == '-') {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (!isValidValue(valueStr)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        double value = std::strtod(valueStr.c_str(), NULL);
        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        try {
            float rate = getRate(date);
            std::cout << date << " => " << value << " = " << (rate * value) << std::endl;
        } catch (...) {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
}