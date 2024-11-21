#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>
#include <vector>

/**
 * @brief Returns the index of the left child of a node in a heap.
 * @param node Index of the node.
 * @return Index of the left child.
 */
inline constexpr size_t heap_left(size_t node) { 
    return 2 * node + 1;
}

/**
 * @brief Returns the index of the right child of a node in a heap.
 * @param node Index of the node.
 * @return Index of the right child.
 */
inline constexpr size_t heap_right(size_t node) { 
    return 2 * node + 2; 
}

/**
 * @brief Returns the index of the parent of a node in a heap.
 * @param node Index of the node.
 * @return Index of the parent.
 */
inline constexpr size_t heap_parent(size_t node) {
    return (node == 0) ? 0 : (node - 1) / 2;
}

/**
 * @brief Performs a preorder traversal of a heap
 * @tparam ArrayLike Type of the heap container.
 * @tparam FN Type of the function to apply.
 * @param heapdata The heap data container.
 * @param heapnodes The number of nodes in the heap.
 * @param node The current node index.
 * @param fn The function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) return; // Stop recursion if node index is out of bounds
    fn(heapdata[node]); // Apply the function
    heap_preorder(heapdata, heapnodes, heap_left(node), fn);
    heap_preorder(heapdata, heapnodes, heap_right(node), fn);
}

/**
 * @brief Performs an inorder traversal of a heap.
 * @tparam ArrayLike Type of the heap container.
 * @tparam FN Type of the function to apply.
 * @param heapdata The heap data container.
 * @param heapnodes The number of nodes in the heap.
 * @param node The current node index.
 * @param fn The function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) return; // Stop recursion if node index is out of bounds
    heap_inorder(heapdata, heapnodes, heap_left(node), fn);
    fn(heapdata[node]); 
    heap_inorder(heapdata, heapnodes, heap_right(node), fn);
}

/**
 * @brief Performs a postorder traversal of a heap and applies a function to each node.
 * @tparam ArrayLike Type of the heap container.
 * @tparam FN Type of the function to apply.
 * @param heapdata The heap data container.
 * @param heapnodes The number of nodes in the heap.
 * @param node The current node index.
 * @param fn The function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) return; // Stop recursion if node index is out of bounds
    heap_postorder(heapdata, heapnodes, heap_left(node), fn);
    heap_postorder(heapdata, heapnodes, heap_right(node), fn); 
    fn(heapdata[node]);
}

/**
 * @brief Performs a level order traversal of a heap and applies a function to each node.
 * @tparam ArrayLike Type of the heap container.
 * @tparam FN Type of the function to apply.
 * @param heapdata The heap data container.
 * @param heapnodes The number of nodes in the heap.
 * @param fn The function to apply to each node.
 */
template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike &heapdata, size_t heapnodes, FN fn) {
    for (size_t i = 0; i < heapnodes; ++i) {
        fn(heapdata[i]); // Apply the function to each node in the container
    }
}

/**
 * @brief Checks if the heap satisfies the heap property.
 * @tparam ArrayLike Type of the heap container.
 * @tparam COMPARISON Type of the comparison function.
 * @param heapdata The heap data container.
 * @param nodes The number of nodes in the heap.
 * @param compare The comparison function (e.g., less or greater).
 * @return True if the heap satisfies the property, otherwise false.
 */
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike &heapdata, size_t nodes, COMPARISON compare) { 
    for (size_t i = 0; i < nodes; ++i) {
        size_t left = heap_left(i); 
        size_t right = heap_right(i); 
        // Check if the current node satisfies the heap property with its children
        if ((left < nodes && !compare(heapdata[i], heapdata[left])) ||
            (right < nodes && !compare(heapdata[i], heapdata[right]))) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Bubbles a node up to maintain the heap property.
 * @tparam RAIterator Random access iterator type.
 * @tparam COMPARE Type of the comparison function.
 * @param begin Iterator pointing to the start of the heap.
 * @param nodes The number of nodes in the heap.
 * @param start The index of the node to bubble up.
 * @param compare The comparison function.
 * @return The number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    size_t swaps = 0; // Track the number
    while (start > 0) {
        size_t parent = heap_parent(start); // Calculate the parent index
        if (!compare(begin[parent], begin[start])) { // Check if parent violates heap property
            std::swap(begin[parent], begin[start]); // Swap parent and current node
            start = parent; 
            ++swaps;
        } else {
            break; // Stop if the heap property is done
        }
    }
    return swaps;
}

/**
 * @brief Bubbles a node down to maintain the heap property.
 * @tparam RAIterator Random access iterator type.
 * @tparam COMPARE Type of the comparison function.
 * @param begin Iterator pointing to the start of the heap.
 * @param nodes The number of nodes in the heap.
 * @param start The index of the node to bubble down.
 * @param compare The comparison function.
 * @return The number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    size_t swaps = 0; 
    size_t current = start; // Start bubbling down

    while (true) {
        size_t left = heap_left(current); 
        size_t right = heap_right(current); 
        size_t smallest = current; 

        if (left < nodes && compare(begin[left], begin[smallest])) {
            smallest = left; // Update smallest if left child is smaller
        }

        if (right < nodes && compare(begin[right], begin[smallest])) {
            smallest = right; // Update smallest if right child is smaller
        }

        if (smallest == current) break; // Stop if current is already smallest

        std::swap(begin[current], begin[smallest]);
        current = smallest; 
        ++swaps;
    }

    return swaps;
}

/**
 * @brief Inserts a new value into the heap and maintains the heap property.
 * @tparam T Type of the value to insert.
 * @tparam CONTAINER Type of the heap container.
 * @tparam COMPARISON Type of the comparison function.
 * @param heapdata The heap data container.
 * @param nodes The number of nodes in the heap (passed by reference).
 * @param key The value to insert.
 * @param compare The comparison function.
 */
template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER &heapdata, size_t &nodes, T key, COMPARISON compare) {
    if (nodes >= heapdata.size()) {
        heapdata.push_back(key); 
    } else {
        heapdata[nodes] = key; // Place the key in the next available position
    }
    ++nodes;
    heap_bubble_up(heapdata.begin(), nodes, nodes - 1, compare);
}

/**
 * @brief Extracts the root value from the heap and maintains the heap property.
 * @tparam CONTAINER Type of the heap container.
 * @tparam COMPARISON Type of the comparison function.
 * @param heapdata The heap data container.
 * @param nodes The number of nodes in the heap (passed by reference).
 * @param compare The comparison function.
 * @return The extracted root value.
 */
template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER &heapdata, size_t &nodes, COMPARISON compare) {
    if (nodes == 0) throw std::runtime_error("Heap is empty"); 
    auto root = heapdata[0];
    heapdata[0] = heapdata[nodes - 1]; // Replace the root with the last element
    --nodes;
    heap_bubble_down(heapdata.begin(), nodes, 0, compare); // Restore the heap property
    return root; 
}

/**
 * @brief Heapifies a range of elements using the bubble-up approach.
 * @tparam RAIterator Random access iterator type.
 * @tparam COMPARE Type of the comparison function.
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param compare The comparison function.
 * @return The number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
    size_t swaps = 0; 
    for (size_t i = 1; i < static_cast<size_t>(end - begin); ++i) {
        swaps += heap_bubble_up(begin, i + 1, i, compare); // Bubble up each element to maintain heap
    }
    return swaps;
}

/**
 * @brief Heapifies a range of elements using the bubble-down approach.
 * @tparam RAIterator Random access iterator type.
 * @tparam COMPARE Type of the comparison function.
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param compare The comparison function.
 * @return The number of swaps performed.
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
    size_t swaps = 0; 
    for (size_t i = static_cast<size_t>(end - begin) / 2; i-- > 0;) {
        swaps += heap_bubble_down(begin, end - begin, i, compare); // Bubble down each non-leaf node
    }
    return swaps; 
}

/**
 * @brief Sorts a range of elements using the heapsort algorithm.
 * @tparam RAIterator Random access iterator type.
 * @tparam COMPARE Type of the comparison function.
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param compare The comparison function.
 */
template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
    heapify_in_place_down(begin, end, compare); // Convert the range into a heap
    for (auto it = end; it != begin; --it) {
        std::swap(*begin, *(it - 1)); // Swap the root 
        heap_bubble_down(begin, it - begin - 1, 0, compare);
    }
}

#endif /* NIU_CSCI340_HEAP_H */



