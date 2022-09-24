#pragma once
#include "pch.h"

#define ALPHA "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Util {
public:
  // Get current date/time in DD-MM-YYYY | HH:mm:ss format
  static const std::string CurrentDateTime();

  static const std::string UpperString(std::string _input);

  static const std::string LowerString(std::string _input);

  template <typename T>
  static const bool IsWholeNum(T _num) {
    return (_num - floor(_num)) != 0 ? false : true;
  }

  /*!*****************************************************************************
  \brief
  Load a text file into a map. The format in text file should be as follows:
  <key1>: <value1>\n
  <key2>: <value2>\n
  <key3>: <value3>\n
  <key4>: <value4>\n

  \param std::fstream& file
  - Input file

  \return std::map<std::string, std::string>
  - Map containing data extracted from file
  *******************************************************************************/
  static std::map<std::string, std::string> TextFileToMap(std::fstream& file);

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
