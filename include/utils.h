#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cctype>
#include <string>

namespace utils {
int stoi(std::string s);
double stod(std::string s);

bool stob(std::string s);

std::string toLowerCase(std::string& s);
std::string toUpperCase(std::string& s);

std::string trim(std::string& s);

std::string itos(int n);
std::string dtos(double n);

std::string to50(std::pair<std::string, std::string>& p);

}  // namespace utils

#endif  // !UTILS_H
