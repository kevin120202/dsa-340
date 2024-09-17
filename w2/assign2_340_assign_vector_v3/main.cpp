#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

#include "assign2-algos.decl.h"


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
    for (auto it = ++begin; it != end; it++) {
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
    for (auto it = ++begin; it != end; it++) {
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

template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS& bin_counts, int N, double width) {
    // XXX This is not implemented. Student is responsible for implementing properly.
    for (int i = 0; i < N; i++) {
        bin_counts[i] = 0;
    }

    for (auto i = begin; i != end; i++) {
        int res = floor(*i / width);
        if (res >= 0 && res <= N - 1) {
            bin_counts[res]++;
        }
    }
}

// template <typename ITERATOR, typename T>
// token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
//     token_info<ITERATOR> just_stop;
//     just_stop.t_begin = end;
//     just_stop.t_end = end;
//     just_stop.t_next = end;

//     // Find the start of the token
//     just_stop.t_begin = begin;
//     while (just_stop.t_begin != end && *just_stop.t_begin == delim) {
//         ++just_stop.t_begin;  // Skip delimiters at the start
//     }

//     // Find the end of the token
//     just_stop.t_end = just_stop.t_begin;
//     while (just_stop.t_end != end && *just_stop.t_end != delim) {
//         ++just_stop.t_end;  // Find the delimiter that ends the token
//     }

//     // Find the start of the next token (after delimiter)
//     just_stop.t_next = just_stop.t_end;
//     if (just_stop.t_next != end) {
//         ++just_stop.t_next;
//     }

//     return just_stop;
// }

// template <typename ITERATOR, typename T>
// token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
//     // XXX This is not implemented. Student is responsible for implementing properly.
//     // This code allows you to avoid an infinite loop before you actually solve
//     // the problem. It is not the correct solution.
//     token_info<ITERATOR> just_stop;
//     just_stop.t_begin = end;
//     just_stop.t_end = end;
//     just_stop.t_next = end;

//     // Look for the delimiter
//     for (auto it = begin; it != end; ++it) {
//         if (*it == delim) {
//             // Set t_end to current position of the delimiter
//             just_stop.t_end = it;

//             // t_next is the iterator after the delimiter
//             just_stop.t_next = std::next(it);

//             // If t_begin == t_end, this means we have a zero-length token
//             return just_stop;
//         }
//     }

//     return just_stop;
// }

template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
    token_info<ITERATOR> token;

    // Set the initial value of t_next to end
    token.t_next = end;

    // If begin is at the end, we have no more tokens to extract
    if (begin == end) {
        token.t_begin = end;
        token.t_end = end;
        return token;
    }

    // Initialize t_begin
    token.t_begin = begin;

    // Look for the delimiter
    for (auto it = begin; it != end; ++it) {
        if (*it == delim) {
            // Set t_end to current position of the delimiter
            token.t_end = it;

            // t_next is the iterator after the delimiter
            token.t_next = std::next(it);

            // If t_begin == t_end, this means we have a zero-length token
            return token;
        }
    }

    // If no delimiter was found, return the remaining range as the last token
    token.t_end = end;
    token.t_next = end;  // No further tokens
    return token;
}


int main() {
    // std::vector<int> vec1{ 8, 6, 7, 5, 3, 0, 9, 1, 800, 22263, 63, 588, 2300, 367473 };
    // std::cout << range_sum(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_avg(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_maxval(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_minval(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_count(vec1.begin(), vec1.end()) << std::endl;
    // pre = "(" ; sep = ") -> (" ; post = ") -> end"  
    // print_range(std::cout, vec1.begin(), vec1.end(), "| ", " | ", " |", 0);
    //                                               pre     sep        post    width   

    // std::vector <int> v = { 1,2,3,4,5,11,12,13,24,25,31,32,33,34,45,52,56,66,67,68,69,71,72,73,78,81,98,99 };
    // std::vector <int> bins1(100);
    // std::vector <int> bins10(10, 0);
    // std::vector <int> bins20(5, 0);

    // std::cout << "HISTOGRAM WITH BINS OF WIDTH 10\n";
    // histogram(v.begin(), v.end(), bins10, 10, 10);
    // print_range(std::cout, bins10.begin(), bins10.end(), "/", "/", "/\n", 2);
    // std::cout << "\n";

    // std::cout << "HISTOGRAM WITH BINS OF WIDTH 20\n";
    // histogram(v.begin(), v.end(), bins20, 5, 20);
    // print_range(std::cout, bins20.begin(), bins20.end(), "/", "/", "/\n", 2);
    // std::cout << "\n";

    std::string source = " Default test string:   you can use  command-line arguments to supply a different string. Markdown emojis :smile::laughing:";
    auto s_info = get_next_token_strict(source.begin(), source.end(), ' ');

    int i = 0;
    while (s_info.t_begin != source.end()) {
        std::cout << "    " << std::setw(4) << i << ": ";
        // print current token
        print_range(std::cout, s_info.begin(), s_info.end(), "\"", "", "\"\n", 0);

        // find next token
        s_info = get_next_token_strict(s_info.t_next, source.end(), ' ');
        ++i;
    }
    std::cout << "  Found " << i << " token(s) in the string.\n\n";

    return 0;
}
