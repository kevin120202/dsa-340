#include "sudoku.h"
#include "grids.h"
#include "settings.h"
#include <fstream>
#include <iostream>
#include <set>

// Initialize the Sudoku grid with all possibilities (1-9) in each cell
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

// Handle constraints for a specific cell (row, column, and subgrid)
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int changes = 0;
  changes += handle_row_for_cell(grid, row, col);
  changes += handle_col_for_cell(grid, row, col);
  changes += handle_subgrid_for_cell(grid, row, col);
  return changes;
}

// Set a cell to a known value
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
  grid.atrc(row, col).clear();          // Clear all possibilities
  grid.atrc(row, col).insert(solution); // Insert the known solution
}

// Set a cell to unknown (all possibilities)
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
  grid.atrc(row, col).clear(); // Clear all possibilities
  for (int i = 1; i <= 9; ++i) {
    grid.atrc(row, col).insert(i); // Insert all possible values
  }
}

// Remove a specific possibility from the cell
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
  grid.atrc(row, col).erase(value); // Remove the specified value
}

// Print the Sudoku grid
void print_sudoku_grid(std::ostream &ost, const SUDOKUGRID &grid, char unknown,
                       char impossible) {
  for (int row = 0; row < 9; ++row) {
    if (row % 3 == 0 && row != 0) {
      ost << "------+-------+------\n";
    }
    for (int col = 0; col < 9; ++col) {
      if (col % 3 == 0 && col != 0) {
        ost << "| ";
      }
      const std::set<int> &cell = grid.atrc(row, col);
      if (cell.empty()) {
        ost << impossible << ' ';
      } else if (cell.size() == 1) {
        ost << *cell.begin() << ' '; // Only one possibility
      } else {
        ost << unknown << ' '; // Multiple possibilities
      }
    }
    ost << '\n';
  }
}

// Handle row constraints for a given cell
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

// Handle column constraints for a given cell
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

// Handle subgrid constraints for a given cell
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

// Load a Sudoku grid from a file
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
  std::ifstream file(filename);
  if (!file) {
    return false;
  }

  initialize_grid(grid);

  char c;
  for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
      file >> c;
      if (c >= '1' && c <= '9') {
        set_sudoku_cell_known(grid, row, col, c - '0');
      }
    }
  }

  return true;
}
