#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string decimal_to_roman(int num) {
    vector<pair<int, string>> roman = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };

    string res = "";

    for (auto& pair : roman) {
        int value = pair.first;
        string symbol = pair.second;
        while (num >= value) {
            res += symbol;
            num -= value;
        }
    }

    return res;
}


// int main()
// {
//     cout << "1:    " << decimal_to_roman(1) << endl;
//     cout << "14:   " << decimal_to_roman(14) << endl;
//     cout << "26:   " << decimal_to_roman(26) << endl;
//     cout << "39:   " << decimal_to_roman(39) << endl;
//     cout << "247:  " << decimal_to_roman(247) << endl;
//     cout << "789:  " << decimal_to_roman(789) << endl;
//     cout << "160:  " << decimal_to_roman(160) << endl;
//     cout << "227:  " << decimal_to_roman(227) << endl;
//     cout << "1099: " << decimal_to_roman(1099) << endl;
//     cout << "1918: " << decimal_to_roman(1918) << endl;
//     cout << "1954: " << decimal_to_roman(1954) << endl;
//     cout << "3999: " << decimal_to_roman(3999) << endl;

//     return 0;
// }