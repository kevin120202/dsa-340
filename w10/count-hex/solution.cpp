#include <iostream>
#include <string>

int count_hex_a(int n) {
    if (n < 0) {
        return -1;
    }

    int count = 0;
    std::string hex = std::to_string(n);

    // Convert the integer n to a hexadecimal string
    hex = "";
    while (n > 0) {
        int remainder = n % 16;
        if (remainder < 10)
            hex = char(remainder + '0') + hex;
        else
            hex = char(remainder - 10 + 'A') + hex;
        n /= 16;
    }

    // Count the occurrences of 'A' in the hex string
    for (char c : hex) {
        if (c == 'A') {
            count++;
        }
    }

    return count;
}
