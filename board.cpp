#include "board.h"

Board::Board() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '-';
        }
    }
    current_player = 1; // Default to player X
}

void Board::set_current_player(int player) {
    current_player = player;
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
    std::cout << "\n\n=======================================================================\n\n";
}

bool Board::isCellEmpty(int row, int col) {
    return (board[row][col] == '-');
}

void Board::insertTarget(int row, int col) {
    if (current_player == 1) {
        board[row][col] = '1';
    } else if (current_player == 0) {
        board[row][col] = '0';
    } else {
        std::cout << "Invalid move. Please try again." << std::endl;
        return;
    }
    current_player = (current_player == 1) ? 0 : 1;
}

int Board::checkWin() {
    for (auto & row : board) {
        if (row[0] != '-' && row[0] == row[1] && row[0] == row[2]) {
            return (row[0] == '1') ? 1 : -1;
        }
    }

    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return (board[0][j] == '1') ? 1 : -1;
        }
    }

    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return (board[0][0] == '1') ? 1 : -1;
    }
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return (board[0][2] == '1') ? 1 : -1;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                return -2; // Game is ongoing
            }
        }
    }

    return 0; // Draw
}

char Board::getCellValue(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[row][col];
    } else {
        return '-';
    }
}

int Board::getCurrentPlayer() {
    return current_player;
}

void Board::reset() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '-';
        }
    }
    current_player = 1;
}

std::vector<Move> Board::actions(Board& original_board) {
    std::vector<Move> arr_of_moves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                Move move;
                move.row = i;
                move.col = j;
                arr_of_moves.push_back(move);
            }
        }
    }
    return arr_of_moves;
}

Move Board::minimax_with_pruning(Board& original_board, int alpha, int beta) {
    Move bestMove;
    if (original_board.checkWin() != -2) {
        bestMove.value = original_board.checkWin();
        bestMove.row = -1;
        bestMove.col = -1;
        return bestMove;
    }

    if (original_board.getCurrentPlayer() == 1) {
        bestMove.value = MIN;
        auto possibleMoves = original_board.actions(original_board);
        for (auto &move : possibleMoves) {
            Board res_board = result(original_board, move);
            Move currentMove = minimax_with_pruning(res_board, alpha, beta);
            if (currentMove.value > bestMove.value) {
                bestMove = currentMove;
                bestMove.row = move.row;
                bestMove.col = move.col;
            }
            alpha = std::max(alpha, bestMove.value);
            if (beta <= alpha) {
                break;
            }
        }
        return bestMove;
    } else {
        bestMove.value = MAX;
        auto possibleMoves = original_board.actions(original_board);
        for (auto &move : possibleMoves) {
            Board res_board = result(original_board, move);
            Move currentMove = minimax_with_pruning(res_board, alpha, beta);
            if (currentMove.value < bestMove.value) {
                bestMove = currentMove;
                bestMove.row = move.row;
                bestMove.col = move.col;
            }
            beta = std::min(beta, bestMove.value);
            if (beta <= alpha) {
                break;
            }
        }
        return bestMove;
    }
}

Board Board::result(Board& original_board, Move& move) {
    Board newBoard = original_board;
    newBoard.insertTarget(move.row, move.col);
    return newBoard;
}

bool Board::Checkstart(Board& original_board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (original_board.board[i][j] != '-') {
                return false;
            }
        }
    }
    return true;
}
