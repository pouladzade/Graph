#ifndef STRINGPARSER_H
#define STRINGPARSER_H
#include <algorithm>
#include <cctype>
#include <locale>
#include<string>
#include<vector>
using namespace std;

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

// extract numbers from a string which contains only numbers and delimeter  string
// example: 1 2 333 55555 0 8888 4 -123
auto extractNumbers(string text , string delimeter) -> vector<int64_t>
{
    vector<int64_t> numbers;
    string str_number = "";
    size_t start = 0;
    size_t found = 0;
    do{
        found = text.find(delimeter , start);
        if (found == std::string::npos)
        {
            if(start < text.length())// in case of last number
            {
                str_number = text.substr(start,text.length()-start);
                numbers.push_back(stoll(str_number));
            }
            break;
        }
        str_number = text.substr(start,found);
        numbers.push_back(stoll(str_number));

        found += delimeter.length();
        start = found;
    }while(1);

    return numbers;

}

// extracts edges from string which contains only numbers and 2 delimiters
// example: 1,2 333,123 0,79896786
auto extractEdges(string text , string delimeter1, string delimeter2)-> vector<pair<int64_t,int64_t>>
{
    vector<pair<int64_t,int64_t>> numbers;
    string str_number1 = "";
    string str_number2 = "";
    size_t start = 0;
    size_t found = 0;
    text = trim_copy(text);

    do{
        // finding first delimiter
        found = text.find(delimeter1 , start);
        if (found == std::string::npos)
            break;
        str_number1 = text.substr(start,found);

        found += delimeter1.length();
        start = found;

        // finding second delimiter
        found = text.find(delimeter2 , start);
        if (found == std::string::npos)
        {// it means it's the last one
            str_number2 = text.substr(start,text.length()-start);
            numbers.push_back(std::make_pair(stoll(str_number1),stoll(str_number2)));
            break;
        }
        str_number2 = text.substr(start,found);
        numbers.push_back(std::make_pair(stoll(str_number1),stoll(str_number2)));

        found += delimeter2.length();
        start = found;

    }while(1);

    return numbers;

}

#endif // STRINGPARSER_H
