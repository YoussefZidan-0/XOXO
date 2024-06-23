#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    char board[3][3]; // 3x3 Tic Tac Toe board
public:
    // Constructor to initialize the board with empty cells
    Board();

    // Function to display the current state of the board
    void displayBoard();

    // Function to insert a player's target ('X' or 'O') at a specific row and column
    void insertTarget(int row, int col);

    // Function to check for a win
    int checkWin();

    char getCellValue(int row, int col);

    char getCurrentPlayerSymbol();

    void reset();
    char current_player;

};

#endif // BOARD_H
