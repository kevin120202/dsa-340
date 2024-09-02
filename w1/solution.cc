/************************************************************************************ *
* NIU CSCI 340 Section 2 *
* Assignment #1
* Kevin Dela Paz - z2017241 *
**
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
**
* This program generates a vector of random ints, copies them in reverse order to another vector, and prints both vectors in a formatted way.
************************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib> // For generating random #.
#include <iomanip> // For printing.

using namespace std;

/**
 * @brief Generates random numbers and fills a vector.
 *
 * This function clears the input vector, reserves space for the specified size,
 * seeds the random number generator with the given seed, and fills the vector
 * with random numbers up to the specified range limit.
 *
 * @param v The vector to be filled with random numbers.
 * @param seed The seed for the random number generator.
 * @param range_limit The upper limit for the random numbers [1 to range_limit].
 * @param vec_size The number of random numbers to generate and fill into the vector.
 */
void gen_rnd_nums(vector < int >& v, int seed, int range_limit, int vec_size) {
    // Clear the vector and allocate enough space.
    v.clear();
    v.reserve(vec_size);

    // Seeding the generator.
    srand(seed);

    // Fill the vector with randomly generated numbers.
    for (int i = 0; i < vec_size; i++) {
        int random_num = rand() % range_limit + 1;
        v.push_back(random_num);
    }
}

/**
 * @brief Copies the elements of one vector into another in reverse order.
 *
 * This function checks if the sizes of the two input vectors are the same. If they are,
 * it copies the elements of the first vector (`v1`) into the second vector (`v2`)
 * in reverse order. It returns -1 if the vectors are of different sizes, otherwise 1.
 *
 * @param v1 The vector whose elements are to be copied in reverse order.
 * @param v2 The vector to receive the reversed elements.
 * @return Returns 1 on successful reverse copy, -1 if vectors have different sizes.
 */
int reverse_copy(vector < int >& v1, vector < int >& v2) {
    // Check if they are equal length.
    if (v1.size() != v2.size()) {
        return -1;
    }

    // Copy elements in reverse order.
    size_t v1_size = v1.size();
    for (size_t i = 0; i < v1_size; i++) {
        v2[i] = v1[v1_size - 1 - i];
    }

    return 1;
}

/**
 * @brief Prints the contents of a vector in a formatted way.
 *
 * This function prints the elements of the input vector, with each element
 * taking up a specified width. It also prints a specified number of items per row.
 *
 * @param v The vector to be printed.
 * @param items_per_row The number of items to print per row.
 * @param item_width The width of each item when printed.
 */
void print_vec(const vector <int>& v, int items_per_row, int item_width) {
    cout << endl;
    // Loops over each num in the vector and prints them in a formatted way.
    for (size_t i = 0; i < v.size(); i++) {
        cout << setw(item_width) << v[i];

        // After printing items_per_row this becomes true and prints a new line.
        if ((i + 1) % items_per_row == 0) {
            cout << endl;
        }
    }

    // Add a newline at the end if the last line isn't complete.
    if (v.size() % items_per_row != 0) {
        std::cout << std::endl;
    }
}

// int main() {
//     //some parameters
//     int rand_up_limit = 1000;
//     int size = 99;
//     int seed = 7;
//     int items_per_row = 10;
//     int width = 8;

//     vector<int> v1, v2;
//     gen_rnd_nums(v1, seed, rand_up_limit, size);

//     // make v2 the same size as v1
//     v2.resize(v1.size());
//     if (reverse_copy(v1, v2) == -1)
//     {
//         cout << "reverse copy failed" << endl;
//         return -1;
//     }

//     cout << endl << "first vector: " << endl;
//     print_vec(v1, items_per_row, width);
//     cout << endl << "second vector: " << endl;
//     print_vec(v2, items_per_row, width);

//     return 0;
// }