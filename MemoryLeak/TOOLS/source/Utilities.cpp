#include "Utilities.h"


const std::string Util::CurrentDateTime() {
  time_t now = time(NULL);
  char time[80];
  struct tm timeStruct;
  localtime_s(&timeStruct, &now);
  strftime(time, sizeof(time), "%d-%m-%Y | %X", &timeStruct);
  return time;
}

const std::string Util::UpperString(std::string _input) {
  std::string result;
  for (char letter : _input) {
    result += (char)(toupper(letter));
  }
  return result;
}

const std::string Util::LowerString(std::string _input) {
  std::string result;
  for (char letter : _input) {
    result += (char)(tolower(letter));
  }
  return result;
}

std::map<std::string, std::string> Util::TextFileToMap(std::fstream& _file) {
  std::map<std::string, std::string> data;

  std::string line{};
  while (std::getline(_file, line)) {
    size_t midpoint{ line.find(':') };

    data.insert({ line.substr(0, midpoint), line.substr(midpoint + 2, midpoint + 2 - line.length()) });
  }

  return data;
}

void Util::MemoryLeak() {
    #include <cstdlib>
    #include <crtdbg.h>

    #ifdef _DEBUG
    #define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    #endif
}
