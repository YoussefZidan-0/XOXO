#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

#define MIN std::numeric_limits<int>::min()
#define MAX std::numeric_limits<int>::max()

struct Move;

class Board {
public:
    char board[3][3];  // 3x3 Tic Tac Toe board.
    int current_player; // to indicate current player (1 for X and 0 for O).

    Board();

    void set_current_player(int player);
    void displayBoard();
    void insertTarget(int row, int col);
    int checkWin();
    char getCellValue(int row, int col);
    int getCurrentPlayer();
    void reset();
    std::vector<Move> actions(Board& original_board);
    Board result(Board& original_board, Move& move);
    Move minimax_with_pruning(Board& original_board, int alpha = MIN, int beta = MAX);
    bool Checkstart(Board& original_board);
    bool isCellEmpty(int row, int col);
};

struct Move {
    int row;
    int col;
    int value; // 1,-1,0 for terminal states, -2 for non-terminal states.
};

#endif // BOARD_H
