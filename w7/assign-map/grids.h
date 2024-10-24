/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #4 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 **
 ************************************************************************************/

#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include "grids.decl.h"
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

// Checks if the given (x, y) coordinates are within the bounds of the grid.
// Returns true if x is between 0 and width (exclusive) and y is between 0 and
// height (exclusive).
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckxy(int x, int y) const {
  // Check if x >= 0 and x < width
  // Check if y >= 0 and y < height
  return x >= 0 and x < _width and y >= 0 and y < _height;
}

// Checks if the given (row, col) coordinates are within the bounds of the grid.
// Returns true if row is between 0 and height (exclusive) and col is between 0
// and width (exclusive).
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckrc(int row, int col) const {
  // Check if row >= 0 and row < height
  // Check if col >= 0 and col < width
  return row >= 0 and row < _height and col >= 0 and col < _width;
}

// Checks if the grid is empty by verifying both width and height are zero.
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::empty() const {
  return _width == 0 and _height == 0;
}

// Clears the grid by removing all elements and resetting width and height to
// zero.
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::clear() {
  // Use the .clear() to remove the elements
  // Set width and height to 0
  data.clear();
  _width = 0;
  _height = 0;
}

template <typename T, typename RA_CONTAINER>
T &grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) {
  // Check if x and y are in bounds by calling the boundcheck methods
  // If not, throw an out_of_range exception
  // return the element at that point
  if (!boundscheckxy(x, y)) {
    throw std::out_of_range("Out of bounds");
  }
  int index = y * _width + x;
  return data[index];
}

// Const version of the atxy() function.
// exception if invalid. Returns a const reference to the element at that point.
template <typename T, typename RA_CONTAINER>
const T &grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) const {
  if (!boundscheckxy(x, y)) {
    throw std::out_of_range("Out of bounds");
  }
  int index = y * _width + x;
  return data[index];
}

template <typename T, typename RA_CONTAINER>
T &grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) {
  // Check if x and y are in bounds by calling the boundcheck methods
  // If not, throw an out_of_range exception
  // return the element at that point
  if (!boundscheckrc(row, col)) {
    throw std::out_of_range("Out of bounds");
  }
  int index = row * _width + col;
  return data[index];
}

// Const version of the atrc() function.
// Returns a const reference to the element at that point.
template <typename T, typename RA_CONTAINER>
const T &grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) const {
  if (!boundscheckrc(row, col)) {
    throw std::out_of_range("Out of bounds");
  }
  int index = row * _width + col;
  return data[index];
}

// Returns the current width of the grid.
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::width() const {
  return _width;
}

// Returns the current height of the grid.
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::height() const {
  return _height;
}

// Assignment operator to copy data from another grid.
// Resizes the current grid to match the dimensions of the source grid and
// copies the data.
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major<T, RA_CONTAINER> &grid_row_major<T, RA_CONTAINER>::operator=(
    const grid_row_major<T, OTHER_CONTAINER> &source) {
  if (this != &source) {
    // Resize the current grid to match the source
    resize(source.width(), source.height());
    // Copy data from the source
    for (int i = 0; i < _height; ++i) {
      for (int j = 0; j < _width; ++j) {
        data[i * _width + j] = source.atrc(i, j);
      }
    }
  }
  return *this;
}

// Returns an iterator to the beginning of the row.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) {
  return data.begin() + (row * _width);
}

// Returns an iterator to the end of the row.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) {
  return data.begin() + ((row + 1) * _width);
}

// Const version of rowbegin() that returns a const iterator to the beginning of
// the row.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) const {
  return data.cbegin() + (row * _width);
}

// Const version of rowend() that returns a const iterator to the end of the
// row.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) const {
  return data.cbegin() + ((row + 1) * _width);
}

// Returns a column iterator pointing to the first element of the column.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colbegin(int col) {
  return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col,
                                                       _width);
}

// Returns a column iterator pointing to the end of the specified column.
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colend(int col) {
  return col_iterator<typename RA_CONTAINER::iterator>(
      data.begin() + col + (_height - 1) * _width, _width);
}

// Resizes the grid to the new width and height.
// If the new dimensions are the same as the current, no changes are made.
// Otherwise, a new container is created and existing data is copied to the new
// container.
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
  if (new_width == _width && new_height == _height)
    return; // No change needed
  RA_CONTAINER new_data(new_width * new_height);

  // Copy existing data to the new container
  for (int row = 0; row < std::min(_height, new_height); ++row) {
    for (int col = 0; col < std::min(_width, new_width); ++col) {
      new_data[row * new_width + col] = data[row * _width + col];
    }
  }

  // Update data and dimensions
  data = std::move(new_data);
  _width = new_width;
  _height = new_height;
}

// Loads grid dimensions and data from a file.
// Returns false if the file cannot be opened; otherwise, resizes the grid
// and populates it with data from the file.
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::load_from_file(
    const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return false;

  int new_width, new_height;
  file >> new_width >> new_height;
  resize(new_width, new_height);

  for (int i = 0; i < new_height; ++i) {
    for (int j = 0; j < new_width; ++j) {
      file >> data[i * new_width + j];
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

// Performs matrix multiplication of two grids.
// Returns false if the number of columns in lhs does not == the number of
// rows in rhs. The result grid is resized to the dimensions and
// filled with the calculated values.
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 &result) {
  if (lhs.width() != rhs.height()) {
    return false; // Incompatible dimensions
  }

  // Initialize result dimensions
  result.resize(lhs.height(), rhs.width());

  for (int i = 0; i < lhs.height(); ++i) {
    for (int j = 0; j < rhs.width(); ++j) {
      double sum = 0;
      for (int k = 0; k < lhs.width(); ++k) {
        sum += lhs.atrc(i, k) * rhs.atrc(k, j);
      }
      result.atrc(i, j) = sum; // Store the result
    }
  }
  return true; // Successful multiplication
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////

// Increments the iterator to the next position in the column.
// Moves to the next element down the column.
template <typename ITERATOR>
auto &col_iterator<ITERATOR>::operator++() { // preincrement
  pos += width; // Move to the next row in the same column
  return *this;
}

template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator++(int) { // postincrement
  col_iterator temp = *this;
  ++(*this); // Use pre-increment
  return temp;
}

template <typename ITERATOR>
col_iterator<ITERATOR> col_iterator<ITERATOR>::operator+(int n) const {
  col_iterator temp = *this;
  temp.pos += width * n; // Move n steps forward in the column
  return temp;
}

template <typename ITERATOR> auto &col_iterator<ITERATOR>::operator[](int n) {
  return *(pos + n * width); // Access the nth element in the column
}

template <typename ITERATOR>
const auto &col_iterator<ITERATOR>::operator[](int n) const {
  return *(pos +
           n * width); // Access the nth element in the column (const version)
}

template <typename ITERATOR> auto &col_iterator<ITERATOR>::operator*() {
  return *pos; // Dereference the iterator to get the current element
}

template <typename ITERATOR>
const auto &col_iterator<ITERATOR>::operator*() const {
  return *pos; // Dereference the iterator to get the current element
}

template <typename ITERATOR>
bool col_iterator<ITERATOR>::operator==(const col_iterator<ITERATOR> &other) {
  return pos == other.pos; // Check if two iterators point to the same position
}

#endif
