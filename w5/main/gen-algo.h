/************************************************************************************
 ** NIU CSCI 340 Section 2 * Assignment #2 Kevin Dela Paz - z2017241 *
 **
 * I certify that everything I am submitting is either provided by the professor
 *for use in * the assignment, or work done by me personally. I understand that
 *if I am caught submitting * the work of others (including StackOverflow or
 *ChatGPT) as my own is an act of Academic * Misconduct and will be punished as
 *such. *
 **
 ************************************************************************************/

#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H

#include "gen-algo.decl.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <vector>

/**
 * @brief Reads lines from the given input stream and calls a callback function
 * for each line.
 *
 * @tparam FN Type of the callback function.
 * @param instream The input stream to read from.
 * @param linecb The callback function to process each line read from the
 * stream.
 * @return The number of lines read from the stream.
 */
template <typename FN> size_t read_lines(std::istream &instream, FN linecb) {
  std::string line;
  size_t count = 0;

  while (std::getline(instream, line)) {
    linecb(line); // call the callback function
    ++count;      // to keep track of how many lines we've processed
  }

  return count;
}

/**
 * @brief Splits a string into tokens based on a delimiter and calls a
 * callback.
 *
 *
 * @tparam FN Type of the callback function.
 * @param instring The input string to be split.
 * @param tokencb The callback function to process.
 * @param delimiter The character used to split the string.
 * @return The number of tokens found.
 */
template <typename FN>
size_t split_string_strict(const std::string &instring, FN tokencb,
                           char delimiter) {
  size_t start = 0; // start index
  size_t count = 0; // counter ot keep track of the token found

  for (size_t end = 0; end < instring.size(); ++end) {
    // check if the current char is the delim
    if (instring[end] == delimiter) {
      std::string token = instring.substr(start, end - start);
      tokencb(token); // Passing lvalue token
      ++count;
      start = end + 1;
    }
  }

  // Handle the last token if the string does not end with a delim
  if (start < instring.size()) {
    std::string last_token = instring.substr(start);
    tokencb(last_token);
    ++count;
  }

  return count;
}

/**
 * @brief Splits a string into tokens based on a delim and calls a
 * callback for each token.
 *
 * This method allows empty tokens in the resulting splits.
 *
 * @tparam FN Type of the callback function.
 * @param instring The input string to be split.
 * @param tokencb The callback function to process each token found.
 * @param delimiter The character used to split the string.
 * @return The number of tokens found.
 */
template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb,
                           char delimiter) {
  size_t start = 0;
  size_t count = 0;

  for (size_t end = 0; end < instring.size(); ++end) {
    if (instring[end] == delimiter) {
      if (end > start) { // Avoid creating an empty token
        std::string token = instring.substr(start, end - start);
        tokencb(token);
        ++count;
      }
      start = end + 1;
    }
  }

  // Handle the last token if the string does not end with a delimiter
  if (start < instring.size()) {
    std::string last_token = instring.substr(start);
    tokencb(last_token); // Pass lvalue last_token
    ++count;
  }

  return count;
}

/**
 * @brief Prints a formatted table
 *
 * @tparam TABLE The type of the table.
 * @tparam ARRLIKE The type of the widths array.
 * @param ost The output stream to print to.
 * @param table The table to print.
 * @param widths The widths of each column.
 * @param maxcol The maximum number of columns to print.
 * @param pre The string to print before each row.
 * @param sep The string to print between columns.
 * @param post The string to print after each row.
 * @param leftalign If true, aligns text to the left; else, aligns to the
 * right.
 */
template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream &ost, const TABLE &table, const ARRLIKE &widths,
                 unsigned int maxcol, const std::string &pre,
                 const std::string &sep, const std::string &post,
                 bool leftalign) {
  for (const auto &row : table) {
    ost << pre; // print prefix
    for (unsigned int i = 0; i < std::min(maxcol, (unsigned int)row.size());
         ++i) {
      if (leftalign) {
        ost << std::left;
      } else {
        ost << std::right;
      }
      ost << std::setw(widths[i]) << row[i]; // Print each column
      if (i != maxcol - 1) {
        ost << sep; // Print separator if not the last column
      }
    }
    ost << post << std::endl; // print suffix
  }
}

/**
 * @brief Calculates the minimum number of columns in a table.
 *
 * @param table The table to look at.
 * @return The minimum number of columns in the table.
 */
int table_min_cols(const STR_TABLE &table) {
  return std::min_element(
             table.begin(), table.end(),
             [](const auto &a, const auto &b) { return a.size() < b.size(); })
      ->size();
}

/**
 * @brief Calculates the widths of each column.
 *
 * @tparam STR_TABLE The type of the table.
 * @param table The table to analyze.
 * @return A vector containing the widths of each column.
 */
template <typename STR_TABLE>
std::vector<int> calc_widths(const STR_TABLE &table) {
  std::vector<int> widths(table[0].size(), 0); // Initialize widths to 0
  for (const auto &row : table) {
    for (size_t i = 0; i < row.size(); ++i) {
      widths[i] =
          std::max(widths[i], (int)row[i].size()); // Calculate max width
    }
  }
  return widths;
}

/**
 * @brief Loads a TSV file into a string table.
 *
 * @param filename The name of the file.
 * @return A table represented as a vector of vectors of strings.
 * @throws std::runtime_error if the file cannot be opened.
 */
STR_TABLE load_tsv(const std::string &filename) {
  STR_TABLE table;
  std::ifstream infile(filename);

  if (!infile) {
    throw std::runtime_error("FIle can't be open");
  }

  // Define the line callback to process each line
  auto line_callback = [&](const std::string &line) {
    std::vector<std::string> row;

    // Corrected token_callback to pass by value
    auto token_callback = [&](std::string token) { row.push_back(token); };

    split_string_strict(line, token_callback, '\t'); // Split line into tokens
    table.push_back(row);                            // Add the row to the table
  };

  read_lines(infile, line_callback); // Read lines and process with callback
  return table;                      // Return the loaded table
}

/**
 * @brief Sorts a table of strings alphabetically based on a specified column.
 *
 * @param table The table to sort.
 * @param col The index of the column to sort by.
 */
void table_sort_alpha(STR_TABLE &table, unsigned int col) {
  std::sort(
      table.begin(), table.end(),
      [col](const std::vector<std::string> &a,
            const std::vector<std::string> &b) { return a[col] < b[col]; });
}

/**
 * @brief Sorts a table of strings numerically based on a specified column.
 *
 * @param table The table to sort.
 * @param col The index of the column to sort by.
 */
void table_sort_numer(STR_TABLE &table, unsigned int col) {
  std::sort(table.begin(), table.end(),
            [col](const std::vector<std::string> &a,
                  const std::vector<std::string> &b) {
              return std::atof(a[col].c_str()) < std::atof(b[col].c_str());
            });
}

#endif
