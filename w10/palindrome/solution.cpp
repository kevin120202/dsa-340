#include <iostream>
#include <cctype>
#include <string>

bool ispalindrome(const std::string& s) {
    int left = 0;
    int right = s.size() - 1;

    while (left < right) {
        // Move left pointer to the next alphanumeric character
        while (left < right && !std::isalnum(s[left])) {
            left++;
        }
        // Move right pointer to the previous alphanumeric character
        while (left < right && !std::isalnum(s[right])) {
            right--;
        }

        // Compare characters, ignoring case
        if (std::tolower(s[left]) != std::tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

