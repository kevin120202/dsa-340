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

template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {
    // Loop from beg to end
    for (auto it = beg; it != end; it++) {
        // Create a newNode
        linked_node <T>* newNode = new linked_node<T>(*it);
        // If head = nullPtr, set head and tail = newNode
        if (n_elements == 0) {
            head = newNode;
            tail = newNode;
        }
        else {
            // Set tail->next to point to the newNode and update tail
            tail->next = newNode;
            tail = newNode;
        }
        n_elements++;
    }
}

template <typename T>
bool simple_linked_list<T>::empty() const {
    return n_elements == 0;
}

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {
    return simple_linked_iterator(head);
}

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
    return simple_linked_iterator<T>(nullptr);
}

template <typename T>
T& simple_linked_list<T>::front() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
}

template <typename T>
T& simple_linked_list<T>::back() {
    if (tail == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}

template <typename T>
void simple_linked_list<T>::pop_back() {
    if (n_elements == 0) return;
    linked_node<T>* temp = tail;  // Store the last node
    if (n_elements == 1) {
        head = nullptr;  // List is now empty
        tail = nullptr;
    }
    else {
        linked_node<T>* prev = head;
        while (prev->next != tail) {  // Find the second to last node
            prev = prev->next;
        }
        tail = prev;                // Update tail to the second to last
        tail->next = nullptr;       // Remove the last node
    }
    delete temp;                   // Free the last node's memory
    n_elements--;
}

template <typename T>
void simple_linked_list<T>::push_back(const T& x) {
    linked_node<T>* newNode = new linked_node<T>(x);
    if (n_elements == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    n_elements++;
}

template <typename T>
simple_linked_list<T>::~simple_linked_list() {
    clear();
}

template <class T>
size_t simple_linked_list<T>::size() const {
    return n_elements;
}

template <typename T>
void simple_linked_list<T>::clear() {
    while (head) {
        linked_node<T>* temp = head; // Store the current head
        head = head->next;            // Move head to the next node
        delete temp;                  // Delete the old head
    }
    tail = nullptr; // Reset tail to nullptr
    n_elements = 0; // Reset the element count
}

// IMPLEMENTATIONS FOR ITERATOR

template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T>& other) const {
    // Compare the positions (node ptrs)
    return pos == other.pos;
}

template <typename T>
simple_linked_iterator <T>& simple_linked_iterator <T>::operator ++ () { // preincrement
    // Move to the next node
    // return the current 
    pos = pos->next;
    return *this;
}

template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
    // Copy the current iterator
    simple_linked_iterator <T> temp = *this;
    // Move to the next node
    pos = pos->next;
    // Return the copy
    return temp;
}

template <typename T>
T& simple_linked_iterator<T>::operator * () { // dereference operator
    return pos->data;
}

#endif
