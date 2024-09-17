#include <iostream>
#include <string>

int main() {
    // Prevent std::cin from skipping spaces
    std::cin >> std::noskipws;

    char ch;
    // Read characters one by one
    while (std::cin >> ch) {
        // Check and replace special characters with corresponding HTML entity
        if (ch == '&') {
            std::cout << "&amp;";
        }
        else if (ch == '<') {
            std::cout << "&lt;";
        }
        else if (ch == '>') {
            std::cout << "&gt;";
        }
        else if (ch == '"') {
            std::cout << "&quot;";
        }
        else if (ch == '\'') {
            std::cout << "&apos;";
        }
        else {
            // If not a special character, just output it as is
            std::cout << ch;
        }
    }

    return 0;
}

