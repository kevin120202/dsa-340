/************************************************************************************
* NIU CSCI 340 Section 2 
*
* Assignment #6 
*
* COREY CHAMBLIS - Z-1955372 
*
* 
*
* I certify that everything I am submitting is either provided by the professor for *
* use in the assignment, or work done by me personally. I understand that if I am *
* caught submitting the work of others (including StackOverflow or ChatGPT) as my *
* own is an act of Academic Misconduct and will be punished as such. 
*
* 
*
* This assignment gives you an opportunity to work with both of the main STL associative *
* container types.                      *
*
*
*
************************************************************************************/


#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"
#include <set>

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

// Define SUDOKUGRID type
typedef grid_row_major<std::set<int>> SUDOKUGRID;

// Checks if (x, y) coordinates are within the grid bounds
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckxy(int x, int y) const 
{
    return x >= 0 && x < _width && y >= 0 && y < _height;
}

// Checks if (row, col) coordinates are within the grid bounds
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckrc(int row, int col) const 
{
    return row >= 0 && row < _height && col >= 0 && col < _width;
}

// Returns true if the grid has no elements
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::empty() const 
{
    return data.empty();
}

// Clears the grid (removes all elements and resets dimensions)
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::clear() 
{
    data.clear();
    _width = 0;
    _height = 0;
}

// Accesses the element at (x, y) with bounds checking
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) 
{
    if (!boundscheckxy(x, y)) throw std::out_of_range("Out of bounds");
    return data[y * _width + x];  // Row-major access
}

// Accesses the element at (x, y) with bounds checking (const version)
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) const 
{
    if (!boundscheckxy(x, y)) throw std::out_of_range("Out of bounds");
    return data[y * _width + x];  // Row-major access
}

// Accesses the element at (row, col) with bounds checking
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) 
{
    if (!boundscheckrc(row, col)) throw std::out_of_range("Out of bounds");
    return data[row * _width + col];  // Row-major access
}

// Accesses the element at (row, col) with bounds checking (const version)
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) const 
{
    if (!boundscheckrc(row, col)) throw std::out_of_range("Out of bounds");
    return data[row * _width + col];  // Row-major access
}

// Returns the width of the grid
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::width() const 
{
    return _width;
}

// Returns the height of the grid
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::height() const 
{
    return _height;
}

// Assignment operator - copies the contents from another grid
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) 
{
    if (this != &source) 
	{
        _width = source._width;
        _height = source._height;
        data.assign(source.data.begin(), source.data.end());
    }
    return *this;
}

// Returns an iterator to the beginning of a row
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) 
{
    return data.begin() + row * _width;
}

// Returns an iterator to the end of a row
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) 
{
    return data.begin() + (row + 1) * _width;
}

// Const version of rowbegin (for read-only access)
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) const 
{
    return data.begin() + row * _width;
}

// Const version of rowend (for read-only access)
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) const 
{
    return data.begin() + (row + 1) * _width;
}

// Returns an iterator to the beginning of a column
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colbegin(int col) 
{
    return col_iterator(data.begin() + col, _width);
}

// Returns an iterator to the end of a column
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colend(int col) 
{
    return col_iterator(data.end() + col, _width);
}

// Resizes the grid to the new width and height
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) 
{
    _width = new_width;
    _height = new_height;
    data.resize(new_width * new_height);  // Adjust the size of the data container
}

// Loads grid data from a file
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::load_from_file(const std::string & filename) 
{
    std::ifstream file(filename);
    if (!file) return false;

    int width, height;
    file >> width >> height;  // Read width and height
    resize(width, height);

    for (int i = 0; i < width * height && file; ++i) 
	{
        file >> data[i];  // Fill the grid with values
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

// Performs matrix multiplication on lhs and rhs, stores result in result grid
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) 
{
    if (lhs.width() != rhs.height()) return false;  // Check if dimensions align

    result.resize(lhs.height(), rhs.width());  // Resize result grid

    for (int i = 0; i < lhs.height(); ++i) 
	{
        for (int j = 0; j < rhs.width(); ++j) 
		{
            result.atrc(i, j) = 0;
            for (int k = 0; k < lhs.width(); ++k) 
			{
                result.atrc(i, j) += lhs.atrc(i, k) * rhs.atrc(k, j);  // Matrix multiplication logic
            }
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//
////////////////////////////////////////////////////////////////////////////////

// Pre-increment operator (moves to the next element in the column)
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () 
{
    pos += width;  // Move to the next row in the column
    return *this;
}

// Post-increment operator (moves to the next element in the column)
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) 
{
    col_iterator tmp = *this;
    ++(*this);
    return tmp;
}

// Adds n to the iterator to move multiple steps
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const 
{
    col_iterator tmp = *this;
    tmp.pos += n * width;
    return tmp;
}

// Access element at position n in the column
template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) 
{
    return *(pos + n * width);
}

// Const version to access element at position n in the column
template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const 
{
    return *(pos + n * width);
}

// Dereference operator (access the element the iterator points to)
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () 
{
    return *pos;
}

// Const version of dereference operator
template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const 
{
    return *pos;
}

// Equality operator (checks if two iterators point to the same position)
template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) 
{
    return pos == other.pos;
}


// Function declarations
void initialize_grid(SUDOKUGRID &grid);
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col);

#endif // NIU_CSCI_340_GRIDS_IMPL_H

