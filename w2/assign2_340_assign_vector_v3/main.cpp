#include <iostream>
#include <vector>
#include <algorithm>

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

int main() {
    std::vector<int> vec1{ 1,3,5,3, 9 };
    // std::cout << range_sum(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_avg(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_maxval(vec1.begin(), vec1.end()) << std::endl;

    // std::cout << range_minval(vec1.begin(), vec1.end()) << std::endl;

    std::cout << range_count(vec1.begin(), vec1.end()) << std::endl;

    return 0;
}
