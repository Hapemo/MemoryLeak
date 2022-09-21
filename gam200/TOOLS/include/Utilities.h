#pragma once
#include "pch.h"

#define ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Util {
public:
    // Get current date/time in DD-MM-YYYY | HH:mm:ss format
    static const std::string CurrentDateTime() {
        time_t now = time(NULL);
        char time[80];
        struct tm timeStruct;
        localtime_s(&timeStruct, &now);
        strftime(time, sizeof(time), "%d-%m-%Y | %X", &timeStruct);
        return time;
    }

    static const std::string UpperString(std::string input) {
        std::string result;
        for (char letter : input) {
            result += (char)(toupper(letter));
        }
        return result;
    }

    static const std::string LowerString(std::string input) {
        std::string result;
        for (char letter : input) {
            result += (char)(tolower(letter));
        }
        return result;
    }

    template <typename T>
    static const bool IsWholeNum(T _num) {
        return (_num - floor(_num)) != 0 ? false : true;
    }

    /*
    static double RoundToDecimal(double _value, int _decimal) {
        if (_decimal < 0) return _value;
        int decimalPlace = 1;
        std::string decimalPlaceStr = std::to_string(decimalPlace);
        for (int i = 0; i < _decimal; ++i) {
            decimalPlaceStr += '0';
        }
        printf("%f\n", roundf(_value * std::stoi(decimalPlaceStr)) / std::stoi(decimalPlaceStr));
        return roundf(_value * std::stoi(decimalPlaceStr)) / std::stoi(decimalPlaceStr);
    }
    */
};
