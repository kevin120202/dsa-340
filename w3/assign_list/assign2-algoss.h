#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H


#include <iomanip>
#include "assign2-algos.decl.h"

// Implement your algorithms for assignment 2 here.

#include <iostream>
#include <string>

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

template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS& bin_counts, int N, double width) {
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

template <typename ITERATOR>
void print_range(std::ostream& ost, ITERATOR begin, ITERATOR end, const std::string& pre, const std::string& sep, const std::string& post, int width) {
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

template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
    double summ = 0;
    for (auto it = begin; it != end; it++) {
        summ += *it;
    }

    return summ;
}

template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
    int num = std::distance(begin, end);
    double summ = range_sum(begin, end);
    double mean = summ / num;

    return mean;
}

template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
    auto maxx = *begin;
    for (auto it = begin; it != end; it++) {
        if (*it > maxx) {
            maxx = *it;
        }
    }

    return maxx;
}

template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
    auto minn = *begin;
    for (auto it = begin; it != end; it++) {
        if (*it < minn) {
            minn = *it;
        }
    }

    return minn;
}

template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
    int num = std::distance(begin, end);

    return num;
}


#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/