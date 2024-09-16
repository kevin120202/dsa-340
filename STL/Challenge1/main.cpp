// Section 20
// Challenge 1
// Identifying palindrome strings using a deque
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// template function to display any deque
template <typename T>
void display(const std::deque<T>& d) {
    std::cout << "[";
    for (const auto& elem : d)
        std::cout << elem << "";
    std::cout << "]" << std::endl;
}

bool is_palindrome(const std::string& s)
{
    std::deque<char> original;

    for (char c : s) {
        if (std::isalpha(c)) {
            original.push_back(std::toupper(c));
        }
    }

    char c1;
    char c2;

    while (original.size() > 1) {
        c1 = original.front();
        c2 = original.back();
        original.pop_front();
        original.pop_back();
        if (c1 != c2) {
            return false;
        }
    }

    return true;


    // std::deque<char> reversed;
    // std::deque<char> original;

    // for (const auto& elem : s) {
    //     if (std::isalpha(elem)) {
    //         char upper = std::toupper(elem);
    //         reversed.push_front(upper);
    //     }
    // }

    // for (const auto& elem : s) {
    //     if (std::isalpha(elem)) {
    //         char upper = std::toupper(elem);
    //         original.push_back(upper);
    //     }
    // }
    // // display(reversed);
    // // display(original);

    // if (reversed == original) {
    //     return true;
    // }

    // return false;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };

    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for (const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s) << s << std::endl;
    }
    std::cout << std::endl;

    // std::cout << is_palindrome("kevinK2");

    return 0;
}