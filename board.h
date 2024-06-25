#ifndef BOARD_H
#define BOARD_H
#include<vector>
#include <iostream>
#include <algorithm>
#include<limits>

#define MIN std::numeric_limits<int>::min()
#define MAX std::numeric_limits<int>::max()
struct Move;

class Board {
public:
    char board[3][3];  // 3x3 Tic Tac Toe board.
    int current_player;// to indicate current player (1 for X and 0 for O).


public:
    //Default Constructor to initialize the board with empty cells.
    Board();

    void set_current_player(int player);
    // Function to display the current state of the board.
    void displayBoard();

    // Function to insert a player's target ('X' or 'O') at a specific row and column.
    void insertTarget(int row, int col);

    // Function to check for a win.
    int checkWin();

    //Function to get cell's value ('1' for X and '0' for O).
    char getCellValue(int row, int col);

    // Function to get the current player to play.
    int getCurrentPlayer();

    void reset();

    // Function to get all possible actions that can be done on the current board.
    std::vector<Move> actions(Board& original_board);


    //function to get the final board if a given move is done.
    Board result(Board& original_board ,Move& move);

    //Function to perform Minimax algorithm with alpha beta pruning.
    Move minimax_with_pruning(Board& original_board,int alpha = MIN, int beta = MAX);

    bool Checkstart(Board& original_board);

    bool  isCellEmpty(int row, int col);
};

struct Move{
    int row;
    int col;
    int value; // 1,-1,0 for terminal states . -2 for non terminal states.
};

#endif