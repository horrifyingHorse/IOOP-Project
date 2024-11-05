#include "../include/utils.h"

int utils::stoi(std::string s) { return (s == "") ? 0 : std::stoi(s); }
int utils::stod(std::string s) { return (s == "") ? 0 : std::stod(s); }

bool utils::stob(std::string s) {
  return (s == "true" || s == "1") ? true : false;
}

std::string utils::toLowerCase(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
   [](unsigned char c) { return std::tolower(c); });

  return s;
}

std::string utils::toUpperCase(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(),
   [](unsigned char c) { return std::toupper(c); });

  return s;
}

std::string utils::trim(std::string& s) {
  s.erase(s.begin(),
    std::find_if(s.begin(), s.end(),
      [](unsigned char c) { return !std::isspace(c); }));

  s.erase(std::find_if(s.rbegin(), s.rend(),
    [](unsigned char c) { return !std::isspace(c); }).base(),
    s.end());

  return s;
}
