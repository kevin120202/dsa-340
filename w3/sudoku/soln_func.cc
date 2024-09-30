#include <vector>
#include <unordered_set>
using namespace std;

bool valid_sudoku(vector<vector<int>>& s) {
    // Check rows
    for (int row = 0; row < 9; ++row) {
        unordered_set<int> seen;
        for (int col = 0; col < 9; ++col) {
            int num = s[row][col];
            if (num != 0) {
                if (seen.count(num)) {
                    return false;
                }
                seen.insert(num);
            }
        }
    }

    // Check cols
    for (int col = 0; col < 9; ++col) {
        unordered_set<int> seen;
        for (int row = 0; row < 9; ++row) {
            int num = s[row][col];
            if (num != 0) {
                if (seen.count(num)) {
                    return false;
                }
                seen.insert(num);
            }
        }
    }

    // Check sub sections
    vector <pair<int, int>> start_i = {
        {0, 0}, {0, 3}, {0, 6},
        {3, 0}, {3, 3}, {3, 6},
        {6, 0}, {6, 3}, {6, 6}
    };

    for (const auto& p : start_i) {
        int row = p.first;
        int col = p.second;
        unordered_set<int> seen;
        for (int i = row; i < row + 3; ++i) {
            for (int j = col; j < col + 3; ++j) {
                int num = s[i][j];
                if (num != 0) {
                    if (seen.count(num)) {
                        return false;
                    }
                    seen.insert(num);
                }
            }
        }
    }

    return true;
}
