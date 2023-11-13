#pragma once

#include <vector>
#include <string>

std::vector<std::string> split_string(const std::string &string, int splits = -1, char seperator = ' ');

int to_int(const std::string &string, bool &success);