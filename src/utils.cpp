#include "../include/utils.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int utils::stoi(std::string s) { return (s == "") ? 0 : std::stoi(s); }
double utils::stod(std::string s) {
  std::stringstream ss(s);
  double value;

  ss >> value;
  if (ss.fail()) {
    return 0;
  }

  std::cout << value << "\n";

  return value;
}

bool utils::stob(std::string s) {
  return (s == "true" || s == "1") ? true : false;
}

std::string utils::toLowerCase(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  return s;
}

std::string utils::toUpperCase(std::string& s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  return s;
}

std::string utils::trim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
            return !std::isspace(c);
          }));

  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char c) { return !std::isspace(c); })
              .base(),
          s.end());

  return s;
}

std::string utils::dtos(double n) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << n;

  return oss.str();
}

std::string utils::itos(int n) { return std::to_string(n); }

std::string utils::to50(std::pair<std::string, std::string>& p) {
  if (p.first.length() + p.second.length() >= 50) return p.first + p.second;

  std::string retStr = "";
  int len = 50 - p.first.length() - p.second.length();

  retStr = p.first;
  for (int i = 0; i < len / 2 - 3; i++) {
    retStr += " ";
  }

  retStr += p.second;
  for (int i = 0; i < len / 2 - 3; i++) {
    retStr += " ";
  }

  return retStr;
}
