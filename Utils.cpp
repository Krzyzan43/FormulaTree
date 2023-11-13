#include <math.h>

#include "Utils.h"


std::vector<std::string> split_string(const std::string &string, int splits, char seperator) {
	
    std::string current_word = "";
    std::vector<std::string> result;

    int last = 0, current = 0;
    while (true)
    {
        last = current = string.find_first_not_of(seperator, current);
        if(current == -1 || splits == result.size())
            break;
        current = string.find(seperator, current);
        result.push_back(string.substr(last, current - last));
    }
    if(current != -1)
        result.push_back(string.substr(current, string.length() - current));
    return result;
}

int to_int(const std::string &str, bool &success)
{
    for (int i = 0; i < str.size(); i++)
    {
        if(str.at(i) < '0' || str.at(i) > '9') {
            success = false;
            return 0;
        }
    }
    success = true; 

    int result = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int exponent = str.length() - i - 1;
        result += (str.at(i) - '0') * pow(10, exponent);
    }
    return result;
}
