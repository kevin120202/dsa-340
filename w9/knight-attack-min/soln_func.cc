#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Position {
    int row, col, moves;
};

// Possible moves of a knight in chess
vector<pair<int, int>> knightMoves = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

int captured(int knight_r, int knight_c, int pawn_r, int pawn_c) {
    // Check if the knight and pawn are on the same square
    if (knight_r == pawn_r && knight_c == pawn_c) {
        return -1;
    }
    
    // Initialize a visited matrix
    vector<vector<bool>> visited(8, vector<bool>(8, false));
    queue<Position> q;
    q.push({knight_r, knight_c, 0});
    visited[knight_r][knight_c] = true;
    
    // BFS loop
    while (!q.empty()) {
        Position curr = q.front();
        q.pop();
        
        // Check if the knight reached the pawn
        if (curr.row == pawn_r && curr.col == pawn_c) {
            return curr.moves;
        }
        
        // Explore all possible knight moves
        for (auto move : knightMoves) {
            int newRow = curr.row + move.first;
            int newCol = curr.col + move.second;
            
            // Check if the new position is within bounds and not visited
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol, curr.moves + 1});
            }
        }
    }
    
    // If no path found, return -1 (this case shouldn't happen on an 8x8 board)
    return -1;
}

