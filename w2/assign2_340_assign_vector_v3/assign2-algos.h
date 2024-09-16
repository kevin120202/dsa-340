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
    just_stop.t_begin = end;
    just_stop.t_end = end;
    just_stop.t_next = end;
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
    return just_stop;
}

template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS& bin_counts, int N, double width) {
    // XXX This is not implemented. Student is responsible for implementing properly.
}

template <typename ITERATOR>
void print_range(std::ostream& ost, ITERATOR begin, ITERATOR end, const std::string& pre, const std::string& sep, const std::string& post, int width) {
    // XXX This is not implemented. Student is responsible for implementing properly.
};

template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    double summ;
    for (auto i = begin; i != end; i++) {
        summ += *i;
    }

    return summ;
}

template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    int num = std::distance(begin, end);
    double summ = range_sum(begin, end);
    double mean = summ / num;

    return mean;
}

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

template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    int num = std::distance(begin, end);

    return num;
}


#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/