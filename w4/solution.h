// The function template takes two forward iterators as input to define the range of elements to be processed.
template<typename ForwardIterator>
void mixNumbers(ForwardIterator begin, ForwardIterator end) {
    // Creating a vector to hold pairs of the form (original index, value) to track original positions.
    std::vector<std::pair<int, int>> elements;
    int index = 0;
    for (auto it = begin; it != end; ++it) {
        elements.emplace_back(index++, *it);
    }

    int size = elements.size();

    // Processing each element based on its original order but considering the current positions.
    for (int i = 0; i < size; ++i) {
        int original_index = elements[i].first;
        int value = elements[i].second;

        if (value == 0) continue; // If the value is 0, it stays in place.

        // Calculate new position taking cyclic nature into account.
        int new_position = (i + value) % size;

        if (new_position < 0) {
            new_position += size; // Adjust for negative wrap-around.
        }

        // Remove the element from the current position.
        auto element = elements[i];
        elements.erase(elements.begin() + i);

        // Insert it at the new position ensuring it's not the first but the last element.
        if (new_position == 0) {
            elements.push_back(element);
        }
        else {
            elements.insert(elements.begin() + new_position, element);
        }

        // Adjust i to ensure we account for the shifted elements.
        i = (i == new_position || new_position == size - 1) ? i : i - 1;
    }

    // Write back the modified sequence into the original range.
    for (int i = 0; i < size; ++i) {
        *(begin + i) = elements[i].second;
    }
}