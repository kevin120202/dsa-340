#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
    // Check if x >= 0 and x < width 
    // Check if y >= 0 and y < height
    return x >= 0 and x < _width and y >= 0 and y < _height;
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
    // Check if row >= 0 and row < height
    // Check if col >= 0 and col < width
    return row >= 0 and row < _height and col >= 0 and col < _width;
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
    // Check if the width and height are both zero
    return _width == 0 and _height == 0;
}

template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
    // Use the .clear() to remove the elements
    // Set width and height to 0
    data.clear();
    _width = 0;
    _height = 0;
}

template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
    // Check if x and y are in bounds by calling the boundcheck methods
    // If not, throw an out_of_range exception
    // return the element at that point
    if(!boundscheckxy(x, y)) {
        throw std::out_of_range("Out of bounds");
    }
    int index = y * _width + x;
    return data[index];
}

template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
    if(!boundscheckxy(x, y)) {
        throw std::out_of_range("Out of bounds");
    }
    int index = y * _width + x;
    return data[index];
}

template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
    // Check if x and y are in bounds by calling the boundcheck methods
    // If not, throw an out_of_range exception
    // return the element at that point
    if(!boundscheckrc(row, col)) {
        throw std::out_of_range("Out of bounds");
    }
    int index = row * _width + col;
    return data[index];
}

template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
    if(!boundscheckrc(row, col)) {
        throw std::out_of_range("Out of bounds");
    }
    int index = row * _width + col;
    return data[index];
}

template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
    return _width;
}

template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
    return _height;
}

template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
  // XXX You are responsible for implementing this function.
}

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {
  // XXX You are responsible for implementing this function.
  return false; // nothing loaded, because you haven't implemented this yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {
  // XXX You are responsible for implementing this function.
  return false; // report that it's not working, because it's not implemented yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////

template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
  // XXX This is not yet implemented
}

template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
  // XXX This is not yet implemented
}
    
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
  // XXX This is not yet implemented
}
    
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
  // XXX This is not yet implemented
}

#endif
