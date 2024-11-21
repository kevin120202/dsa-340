#ifndef NIU_CSCI340_HEAP_PQ_H
#define NIU_CSCI340_HEAP_PQ_H

#include "heap_priority_queue.decl.h"
#include "heap.h"

/**
 * @brief Constructs a priority queue from a range of elements.
 * @tparam T Type of the elements in the priority queue.
 * @tparam CONTAINER Type of the underlying container for the heap.
 * @tparam COMPARE Comparison function type.
 * @tparam ITERATOR Iterator type for the input range.
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 */
template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T, CONTAINER, COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end) {
    data.insert(data.end(), begin, end);
    nodes = data.size();

    // Convert the container into a valid heap in-place
    heapify_in_place_down(data.begin(), data.end(), compare);
}

/**
 * @brief Returns a reference to the top element in the priority queue.
 * @return Reference to the top element.
 * @throws std::runtime_error if the priority queue is empty.
 */
template <class T, class CONTAINER, class COMPARE>
T &heap_priority_queue<T, CONTAINER, COMPARE>::top() {
    if (nodes == 0) throw std::runtime_error("Heap is empty");
    return data[0];
}

/**
 * @brief Checks if the priority queue is empty.
 * @return True if the priority queue is empty, otherwise false.
 */
template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T, CONTAINER, COMPARE>::empty() const {
    return nodes == 0;
}

/**
 * @brief Returns the number of elements in the priority queue.
 * @return The number of elements in the priority queue.
 */
template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T, CONTAINER, COMPARE>::size() const {
    return nodes;
}

/**
 * @brief Pushes a new element into the priority queue.
 * @param x The element to push into the priority queue.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::push(const T &x) {
    data.push_back(x);
    ++nodes;
    heap_bubble_up(data.begin(), nodes, nodes - 1, compare);
}

/**
 * @brief Removes the top element from the priority queue.
 * @throws std::runtime_error if the priority queue is empty.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::pop() {
    // exception if the heap is empty
    if (nodes == 0) throw std::runtime_error("Heap is empty");

    // Swap the root element with the last element in the container
    std::swap(data[0], data[nodes - 1]);

    data.pop_back();

    --nodes;

    // Restore the heap property by bubbling down the new root
    heap_bubble_down(data.begin(), nodes, 0, compare);
}

/**
 * @brief Outputs the contents of the priority queue to the given stream.
 * @param ost The output stream to write to.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::dump_data(std::ostream &ost) const {
    ost << "[ ";
    // Iterate over the elements and output them to the stream
    for (size_t i = 0; i < nodes; ++i) {
        ost << data[i] << " ";
    }
    ost << "]";
}

#endif /* NIU_CSCI340_HEAP_PQ_H */

