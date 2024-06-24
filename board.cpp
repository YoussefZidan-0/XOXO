#include "board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '-';
        }
    }
    //current_player = 1; // Removed: Default player will be set externally
}

void Board::displayBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '1') {
                std::cout << 'X' << " ";
            } else if (board[i][j] == '0') {
                std::cout << 'O' << " ";
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::isCellEmpty(int row, int col) {
    return board[row][col] == '-';
}

bool Board::isCellEmptyPublic(int row, int col) {
    return isCellEmpty(row, col);
}

void Board::insertTarget(int row, int col) {
    // Check if the cell is empty
    if (!isCellEmpty(row, col)) {
        return; // Exit the function if cell is not empty
    }

    // Check if the target is valid ('X' or 'O')
    if (current_player == 1) {
        board[row][col] = 'X';
    } else if (current_player == 0) {
        board[row][col] = 'O';
    } else {
        // Invalid target
        std::cout << "Invalid move. Please try again." << std::endl;
        return; // Exit the function if target is invalid
    }
    // Switch players
    current_player = (current_player == 1) ? 0 : 1;
}

int Board::checkWin() {
    // Check rows for a win
    for (auto & row : board) {
        if (row[0] != '-' && row[0] == row[1] && row[0] == row[2]) {
            if (row[0] == 'X') {
                return 1; // X wins
            } else if (row[0] == 'O') {
                return 0; // O wins
            }
        }
    }

    // Check columns for a win
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            if (board[0][j] == 'X') {
                return 1; // X wins
            } else if (board[0][j] == 'O') {
                return 0; // O wins
            }
        }
    }

    // Check diagonals for a win
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        if (board[0][0] == 'X') {
            return 1; // X wins
        } else if (board[0][0] == 'O') {
            return 0; // O wins
        }
    }
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        if (board[0][2] == 'X') {
            return 1; // X wins
        } else if (board[0][2] == 'O') {
            return 0; // O wins
        }
    }

    // Check for a draw
    bool draw = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                draw = false;
                break;
            }
        }
    }
    if (draw) {
        return -1; // Draw
    }

    return -2; // No winner yet
}

char Board::getCellValue(int row, int col)  {
    // Check if the row and column are within bounds (0 to 2)
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[row][col];
    } else {
        return '-'; // Return empty cell if out of bounds
    }
}

char Board::getCurrentPlayerSymbol()  {
    return current_player;
}

void Board::reset() {
    // Reset the Tic Tac Toe board to its initial state
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '-';
        }
    }
    current_player = 1; // Reset current player to 'X'
}
