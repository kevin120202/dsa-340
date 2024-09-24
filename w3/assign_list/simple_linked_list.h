/************************************************************************************ *
* NIU CSCI 340 Section 2 *
* Assignment #3
* Kevin Dela Paz - z2017241 *
**
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
**
************************************************************************************/

#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>

// Constructor that copies the contents of another container from an iterator range [beg, end].
// ITERATOR beg: The beginning iterator of the range.
// ITERATOR end: The end iterator of the range.
template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {
    for (auto it = beg; it != end; ++it) {
        push_back(*it); // Use push_back to insert each element from the range.
    }
}

// Checks if the linked list is empty.
// Returns true if the list has no elements, false otherwise.
template <typename T>
bool simple_linked_list<T>::empty() const {
    return n_elements == 0;
}

// Returns an iterator pointing to the first element of the list.
// Returns a simple_linked_iterator at the head of the list.
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {
    return simple_linked_iterator<T>(head);
}

// Returns an iterator pointing to one past the last element of the list (tail->next, which is nullptr).
// Returns a simple_linked_iterator at the end (null after the last element).
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
    return simple_linked_iterator<T>(tail->next);
}

// Returns a reference to the first element (front) of the linked list.
// Returns reference to the data in the head node.
template <typename T>
T& simple_linked_list<T>::front() {
    return head->data;
}

// Returns a reference to the last element (back) of the linked list.
// Returns reference to the data in the tail node.
template <typename T>
T& simple_linked_list<T>::back() {
    return tail->data;
}

// Removes the last element from the list (tail element).
// Decrements n_elements and properly adjusts the tail pointer.
template <typename T>
void simple_linked_list<T>::pop_back() {
    if (n_elements == 0) return;
    if (n_elements == 1) {
        delete head;
        head = tail = nullptr;
    }
    else {
        linked_node<T>* temp = head; // Traverse to the second to last node.
        while (temp->next != tail) {
            temp = temp->next;
        }
        // Delete last node. Set new tail to the second to last node and update tail pointer.
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    --n_elements;
}

// Adds a new element to the end of the linked list.
// const T& x: The element to add to the list.
template <typename T>
void simple_linked_list<T>::push_back(const T& x) {
    linked_node<T>* newNode = new linked_node<T>(x); // Create a new node.
    if (n_elements == 0) { // If list is empty, head and tail point to the new node.
        head = tail = newNode;
    }
    else {
        tail->next = newNode; // Link the new node to tail and adjust tail.
        tail = newNode;
    }
    tail->next = nullptr;
    ++n_elements;
}

// Destructor to clean up the linked list by deleting all nodes.
template <typename T>
simple_linked_list<T>::~simple_linked_list() {
    clear();
}

// Returns the number of elements in the linked list.
// Returns the size as size_t.
template <class T>
size_t simple_linked_list<T>::size() const {
    return n_elements;
}

// Clears the list by deleting all nodes and resetting head and tail pointers.
template <typename T>
void simple_linked_list<T>::clear() {
    while (head != nullptr) {
        linked_node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    n_elements = 0;
}

// IMPLEMENTATIONS FOR ITERATOR

// Compares two iterators checking if they point to the same node.
// const simple_linked_iterator<T>& other: The iterator to compare with.
template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T>& other) const {
    return pos == other.pos;
}

// Pre-increment operator: Moves the iterator to the next node.
// Returns reference to the updated iterator.
template <typename T>
simple_linked_iterator <T>& simple_linked_iterator <T>::operator ++ () { // preincrement
    pos = pos->next;
    return *this;
}

// Post-increment operator: Moves the iterator to the next node, but returns the current iterator.
// Returns a copy of the iterator before the increment.
template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
    simple_linked_iterator<T> temp = *this;
    pos = pos->next;
    return temp;
}

// Dereference operator: Returns a reference to the data in the node the iterator points to.
// Returns a reference to the node's data.
template <typename T>
T& simple_linked_iterator<T>::operator * () { // dereference operator
    return pos->data;
}

#endif
