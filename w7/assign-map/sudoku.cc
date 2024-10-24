/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #6 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *

 This file includes functions to initialize the grid with all possible values
 (1-9) for each cell, set specific cells to known values, and reset them. It
 also handles Sudoku constraints by removing possibilities from other cells in
 the same row, column, and 3x3 subgrid when a value is determined.
 ************************************************************************************/

#include "sudoku.h"
#include "grids.h"
#include "settings.h"
#include <fstream>
#include <iostream>
#include <set>

/**
 * @brief Initialize the Sudoku grid.
 *
 * This function resizes the grid to 9x9 and populates each cell with a set of
 * integers from 1 to 9
 *
 * @param grid The Sudoku grid to be initialized.
 */
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9, 9); // Resize the grid to 9x9
  for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
      grid.atrc(row, col) = std::set<int>{
          1, 2, 3, 4, 5,
          6, 7, 8, 9}; // Set all cells to contain all possibilities
    }
  }
}

/**
 * @brief Handle constraints for a specific cell (row, column, and subgrid).
 *
 * This function checks the constraints for the  cell in terms of its row,
 * column, and 3x3 subgrid. It updates the possibilities for the cell based on
 * the current state of the Sudoku grid.
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The number of changes made to the cell's possibilities.
 */
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int changes = 0;
  changes += handle_row_for_cell(grid, row, col);
  changes += handle_col_for_cell(grid, row, col);
  changes += handle_subgrid_for_cell(grid, row, col);
  return changes;
}

/**
 * @brief Set a cell to a known value.
 *
 * This function updates the specified cell in the grid to contain a known
 * solution. It clears all existing possibilities
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param solution The known solution to be set in the cell.
 */
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
  grid.atrc(row, col).clear();          // Clear all possibilities
  grid.atrc(row, col).insert(solution); // Insert the known solution
}

/**
 *
 * This function resets the specified cell to contain all possible values
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 */
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
  grid.atrc(row, col).clear(); // Clear all possibilities
  for (int i = 1; i <= 9; ++i) {
    grid.atrc(row, col).insert(i); // Insert all possible values
  }
}

/**
 * @brief Remove a specific possibility from the cell.
 *
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param value The value to be removed from the cell's possibilities.
 */
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
  grid.atrc(row, col).erase(value); // Remove the specified value
}

/**
 * @brief Print the Sudoku grid.
 *
 * @param ost The output stream to print the grid to.
 * @param grid The Sudoku grid to be printed.
 * @param unknown Character representing cells with unknown possibilities.
 * @param impossible Character representing cells that have no valid
 * possibilities.
 */
void print_sudoku_grid(std::ostream &ost, const SUDOKUGRID &grid, char unknown,
                       char impossible) {
  for (int row = 0; row < 9; ++row) {
    if (row % 3 == 0 && row != 0) {
      ost << "------+-------+------\n"; // Print separator for 3x3 grids
    }
    for (int col = 0; col < 9; ++col) {
      if (col % 3 == 0 && col != 0) {
        ost << "| ";
      }
      const std::set<int> &cell = grid.atrc(row, col);
      if (cell.empty()) {
        ost << impossible << ' '; // No valid possibilities
      } else if (cell.size() == 1) {
        ost << *cell.begin() << ' '; // Only one possibility
      } else {
        ost << unknown << ' '; // Multiple possibilities
      }
    }
    ost << '\n'; // New line for the next row
  }
}

/**
 * @brief Handle row constraints for a given cell.
 *
 * This function removes the value from other cells in the same row if the
 * specified cell has only one possibility.
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The number of changes made to other cells in the row.
 */
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;
  const std::set<int> &cell = grid.atrc(row, col);
  if (cell.size() == 1) {
    int value = *cell.begin();
    for (int c = 0; c < 9; ++c) {
      if (c != col) {
        count += grid.atrc(row, c).erase(
            value); // Remove value from other cells in the row
      }
    }
  }
  return count;
}

/**
 * @brief Handle column constraints for a given cell.

 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The number of changes made to other cells in the column.
 */
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;
  const std::set<int> &cell = grid.atrc(row, col);
  if (cell.size() == 1) {
    int value = *cell.begin();
    for (int r = 0; r < 9; ++r) {
      if (r != row) {
        count += grid.atrc(r, col).erase(
            value); // Remove value from other cells in the column
      }
    }
  }
  return count;
}

/**
 * @brief Handle subgrid constraints for a given cell.
 *
 * @param grid The Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return The number of changes made to other cells in the subgrid.
 */
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;
  const std::set<int> &cell = grid.atrc(row, col);
  if (cell.size() == 1) {
    int value = *cell.begin();
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int r = start_row; r < start_row + 3; ++r) {
      for (int c = start_col; c < start_col + 3; ++c) {
        if (r != row || c != col) {
          count += grid.atrc(r, c).erase(
              value); // Remove value from other cells in the subgrid
        }
      }
    }
  }
  return count;
}

/**
 * @brief Load a Sudoku grid from a file.
 *
 * This function reads a Sudoku puzzle from a file. It initializes
 * the grid and sets known values based on the contents of the file. The
 * format of the file is expected to be 9 lines of 9 characters.
 *
 * @param filename The name of the file.
 * @param grid The Sudoku grid to be filled with values from the file.
 * @return true if the grid was loaded successfully, false otherwise.
 */
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
  initialize_grid(grid); // Initialize the grid
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << '\n';
    return false;
  }

  for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
      char ch;
      file >> ch; // Read character from the file
      if (ch >= '1' && ch <= '9') {
        set_sudoku_cell_known(grid, row, col, ch - '0'); // Set known values
      } else {
        set_sudoku_cell_unknown(grid, row, col); // Set cells as unknown
      }
    }
  }
  return true; // Successfully loaded the grid
}
