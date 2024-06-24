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


void Board::reset() {
    // Reset the Tic Tac Toe board to its initial state
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '-';
        }
    }
    current_player = 1; // Reset current player to 'X'
}

int Board::getCurrentPlayer() {
    return current_player;
}



std::vector<Move> Board::actions(Board& original_board) {
    std::vector<Move> arr_of_moves;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(board[i][j] == '-'){
                Move move;
                if(current_player == 1)
                {
                    board[i][j] = '1'; //  X if its turn
                }
                else
                {
                    board[i][j] = '0'; // O if its turn
                }
                move.row = i;
                move.col = j;
                arr_of_moves.push_back(move);
                board[i][j] = '-';
            }
        }
    }
    return arr_of_moves;
}


Move Board::minimax_with_pruning(Board& original_board ,int alpha, int beta){
    Move bestMove;
    if(original_board.checkWin() != -2)
    {
        bestMove.value = original_board.checkWin();
        //any invalid values
        bestMove.row = -1;
        bestMove.col = -1;
        return bestMove;
    }

    //maximizer(X)
    if(original_board.getCurrentPlayer() == 1)
    {
        bestMove.value = MIN;
        std::vector<Move> possibleMoves = original_board.actions(original_board);
        for(auto &move : possibleMoves)
        {
            Board res_board = result(original_board , move);
            Move currentMove = minimax_with_pruning(res_board,alpha, beta);
            if (currentMove.value > bestMove.value) {
                bestMove = currentMove;
                bestMove.row = move.row;
                bestMove.col = move.col;
            }

            alpha = std::max(alpha, bestMove.value);
            if(beta <= alpha){
                break; // beta cut-off
            }
        }

        return bestMove;

    }

    //minimizer(O)
    if(original_board.getCurrentPlayer() == 0)
    {
        bestMove.value = MAX;
        std::vector<Move> possibleMoves = original_board.actions(original_board);
        for(auto &move : possibleMoves)
        {
            Board res_board = result(original_board , move);
            Move currentMove = minimax_with_pruning(res_board,alpha, beta);
            if (currentMove.value < bestMove.value) {
                bestMove = currentMove;
                bestMove.row = move.row;
                bestMove.col = move.col;
            }

            beta = std::min(beta, bestMove.value);
            if(beta <= alpha){
                break; // alpha cut-off
            }
        }
        return bestMove;
    }
}


Board Board::result(Board& original_board ,Move& move) {
    // Create a new board by copying the state
    Board newBoard = original_board;

    // Apply the move to the new board
    newBoard.insertTarget(move.row, move.col);

    // Return the resulting board

    return newBoard;
}

bool Board::Checkstart(Board& original_board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (original_board.board[i][j] != '-') {
                return false; // A cell is not empty
            }
        }
    }
    return true; // All cells are empty
}