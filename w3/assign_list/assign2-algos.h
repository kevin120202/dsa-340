/************************************************************************************ *
* NIU CSCI 340 Section 2 *
* Assignment #2
* Kevin Dela Paz - z2017241 *
**
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
**
* This program calculates basic statistical properties (count, sum, average, maximum, and minimum values) for a given range of numbers.
************************************************************************************/

#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H


#include <iomanip>
#include "assign2-algos.decl.h"

// Implement your algorithms for assignment 2 here.

#include <iostream>
#include <string>

/**
 * @brief Tokenizes a range of elements, strictly stopping at the first delimiter found.
 *
 * This function identifies a token between two delimiters or until the end of the range.
 *
 * @tparam ITERATOR An iterator type.
 * @tparam T The delimiter type.
 * @param begin Iterator pointing to the beginning of the range.
 * @param end Iterator pointing to the end of the range.
 * @param delim The delimiter used to split the token.
 * @return A token_info object that contains the range of the token and the next position.
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    // This code allows you to avoid an infinite loop before you actually solve
    // the problem. It is not the correct solution.
    token_info<ITERATOR> just_stop;

    // Set the initial value of t_next to end
    just_stop.t_next = end;

    // If begin is at the end, we have no more tokens to extract
    if (begin == end) {
        just_stop.t_begin = end;
        just_stop.t_end = end;
        return just_stop;
    }

    // Initialize t_begin
    just_stop.t_begin = begin;

    // Look for the delimiter
    for (auto it = begin; it != end; ++it) {
        if (*it == delim) {
            // Set t_end to current position of the delimiter
            just_stop.t_end = it;

            // t_next is the iterator after the delimiter
            just_stop.t_next = std::next(it);

            // If t_begin == t_end, this means we have a zero-length token
            return just_stop;
        }
    }

    // If no delimiter was found, return the remaining range as the last token
    just_stop.t_end = end;
    just_stop.t_next = end;  // No further tokens
    return just_stop;
}

/**
 * @brief Tokenizes a range of elements, skipping delimiters at the beginning.
 *
 * This function greedily finds a token by skipping multiple delimiters at the start.
 *
 * @tparam ITERATOR An iterator type for the input range.
 * @tparam T The delimiter type.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @param delim The delimiter used to split the token.
 * @return A token_info object with the range of the next token and the position after the delimiter.
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    // This code allows you to avoid an infinite loop before you actually solve
    // the problem. It is not the correct solution.
    token_info<ITERATOR> just_stop;
    just_stop.t_begin = end;
    just_stop.t_end = end;
    just_stop.t_next = end;

    // Find the start of the token
    just_stop.t_begin = begin;
    while (just_stop.t_begin != end && *just_stop.t_begin == delim) {
        ++just_stop.t_begin;  // Skip delimiters at the start
    }

    // Find the end of the token
    just_stop.t_end = just_stop.t_begin;
    while (just_stop.t_end != end && *just_stop.t_end != delim) {
        ++just_stop.t_end;  // Find the delimiter that ends the token
    }

    // Find the start of the next token after delim
    just_stop.t_next = just_stop.t_end;
    if (just_stop.t_next != end) {
        ++just_stop.t_next;
    }

    return just_stop;
}

/**
 * @brief Generates a histogram for a given range of values.
 *
 * This function bins the values in the range into histogram bins based on the width.
 *
 * @tparam ITERATOR Iterator type for the input data range.
 * @tparam RANDOM_ACCESS Container type for the bin counts.
 * @param begin Iterator pointing to the beginning of the data range.
 * @param end Iterator pointing to the end of the data range.
 * @param bin_counts A container to store the count of values falling into each bin.
 * @param N Number of bins.
 * @param width The width of each bin.
 */
template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS& bin_counts, int N, double width) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    for (int i = 0; i < N; i++) {
        bin_counts[i] = 0;
    }

    // For each value, determine its bin and increment the count
    for (auto i = begin; i != end; i++) {
        int res = *i / width;
        if (res >= 0 && res <= N - 1) {
            bin_counts[res]++;
        }
    }
}

/**
 * @brief Prints a range of elements to an output stream.
 *
 * The function outputs the elements of the range in a formatted manner using a prefix,
 * separator, and postfix.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param ost Output stream to write the elements to.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @param pre Prefix to print before the range.
 * @param sep Separator between elements.
 * @param post Postfix to print after the range.
 * @param width Width of each element when printed.
 */
template <typename ITERATOR>
void print_range(std::ostream& ost, ITERATOR begin, ITERATOR end, const std::string& pre, const std::string& sep, const std::string& post, int width) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    ost << pre;
    bool first = true;

    for (auto it = begin; it != end; ++it) {
        if (!first) {
            ost << sep;
        }
        ost << std::setw(width) << *it;  // Print each element with the width
        first = false;
    }

    ost << post;
};

/**
 * @brief Computes the sum of elements in a range.
 *
 * This function calculates the total sum of all elements in the specified range.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @return The sum of the elements in the range.
 */
template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    double summ = 0;
    for (auto it = begin; it != end; it++) {
        summ += *it;
    }

    return summ;
}

/**
 * @brief Computes the average of elements in a range.
 *
 * This function calculates the average value of the elements in the range.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @return The average value of the elements.
 */
template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    if (begin == end) return 0;  // Handle the empty range case

    double summ = range_sum(begin, end);
    int num = range_count(begin, end);

    return summ / num;
}

/**
 * @brief Finds the maximum value in a range.
 *
 * This function iterates over the range to find the largest element.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @return The maximum value in the range.
 */
template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    auto maxx = *begin;
    for (auto it = begin; it != end; it++) {
        if (*it > maxx) {
            maxx = *it;
        }
    }

    return maxx;
}

/**
 * @brief Finds the minimum value in a range.
 *
 * This function iterates over the range to find the smallest element.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @return The minimum value in the range.
 */
template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    auto minn = *begin;
    for (auto it = begin; it != end; it++) {
        if (*it < minn) {
            minn = *it;
        }
    }

    return minn;
}

/**
 * @brief Finds the minimum value in a range.
 *
 * This function returns the count of elements between the two iterators.
 *
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to the end of the range.
 * @return The count of elements.
 */
template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    int num = 0;
    while (begin != end) {
        ++begin;  // Move to the next element
        ++num;    // Increment the count
    }
    return num;
}


#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/