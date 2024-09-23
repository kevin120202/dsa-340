#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>

template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {
    for (auto it = beg; it != end; ++it) {
        push_back(*it);
    }
}

template <typename T>
bool simple_linked_list<T>::empty() const {
    return n_elements == 0;
}

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {
    return simple_linked_iterator<T>(head);
}

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
    return simple_linked_iterator<T>(tail->next);
}

template <typename T>
T& simple_linked_list<T>::front() {
    return head->data;
}

template <typename T>
T& simple_linked_list<T>::back() {
    return tail->data;
}

template <typename T>
void simple_linked_list<T>::pop_back() {
    if (n_elements == 0) return;
    if (n_elements == 1) {
        delete head;
        head = tail = nullptr;
    }
    else {
        linked_node<T>* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    --n_elements;
}

template <typename T>
void simple_linked_list<T>::push_back(const T& x) {
    linked_node<T>* newNode = new linked_node<T>(x);
    if (n_elements == 0) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    tail->next = nullptr;
    ++n_elements;
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
    while (head != nullptr) {
        linked_node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    n_elements = 0;
}

// IMPLEMENTATIONS FOR ITERATOR

template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T>& other) const {
    return pos == other.pos;
}

template <typename T>
simple_linked_iterator <T>& simple_linked_iterator <T>::operator ++ () { // preincrement
    pos = pos->next;
    return *this;
}

template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
    simple_linked_iterator<T> temp = *this;
    pos = pos->next;
    return temp;
}

template <typename T>
T& simple_linked_iterator<T>::operator * () { // dereference operator
    return pos->data;
}

#endif
