#include <iostream>
using namespace std;

class Board {
private:
    char board[3][3]; // 3x3 Tic Tac Toe board

public:
    // Constructor to initialize the board with empty cells
    Board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = '-';
            }
        }
    }

    // Function to display the current state of the board
    void displayBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '1') {
                    cout << 'X' << " ";
                } else if (board[i][j] == '0') {
                    cout << 'O' << " ";
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // Function to insert a player's target ('X' or 'O') at a specific row and column
    void insertTarget(int row, int col, char target) {
        // Check if the cell is empty before inserting
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '-') {
            if (target == 'X' || target == 'x') {
                board[row][col] = '1';
            } else if (target == 'O' || target == 'o') {
                board[row][col] = '0';
            } else {
                cout << "Invalid move. Please try again." << endl;
            }
        } else {
            cout << "Invalid move. Please try again." << endl;
        }
    }

    // Function to check for a win
    int checkWin() {
        // Check rows for a win
        for (auto & row : board) {
            if (row[0] != '-' && row[0] == row[1] && row[0] == row[2]) {
                if (row[0] == '1') {
                    return 1; // X wins
                } else if (row[0] == '0') {
                    return 0; // O wins
                }
            }
        }

        // Check columns for a win
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] != '-' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
                if (board[0][j] == '1') {
                    return 1; // X wins
                } else if (board[0][j] == '0') {
                    return 0; // O wins
                }
            }
        }

        // Check diagonals for a win
        if (board[0][0] != '-' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            if (board[0][0] == '1') {
                return 1; // X wins
            } else if (board[0][0] == '0') {
                return 0; // O wins
            }
        }
        if (board[0][2] != '-' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            if (board[0][2] == '1') {
                return 1; // X wins
            } else if (board[0][2] == '0') {
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

};
int main() {
    Board gameBoard;

    // Display the initial empty board
    cout << "Initial board:" << endl;
    gameBoard.displayBoard();

    while (gameBoard.checkWin() == -2) {
        int row, col;
        char character;

        cout << "Enter row, column, and character (X or O) separated by Enter: ";
        cin >> row >> col >> character;

        // Check if the character is valid ('X', 'O', 'x', or 'o')
        if ((character == 'X' || character == 'x') || (character == 'O' || character == 'o')) {
            // Insert the target at the specified row and column
            gameBoard.insertTarget(row, col, character);

            // Display the updated board
            cout << "Updated board:" << endl;
            gameBoard.displayBoard();
        } else {
            cout << "Invalid character. Please enter X or O." << endl;
        }
    }

    // Determine the winner or if it's a draw
    int result = gameBoard.checkWin();
    if (result == 1) {
        cout << "X wins!" << endl;
    } else if (result == 0) {
        cout << "O wins!" << endl;
    } else if (result == -1) {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
