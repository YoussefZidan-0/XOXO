#include "mainwindow.h"
#include "board.h"
#include <QApplication>
#include <QPixmap>
// char current_player=1; // 1 for 'X', 0 for 'O'

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
/*
#include <iostream>
#include "board.h"
#include<cstring>
using namespace std;
int main() {
    Board game;
    game.displayBoard();
    int r, c;
    char xo;
    bool notvalid = true;

    // User chooses X or O
    while (notvalid) {
        cout << "Enter X or O: ";
        cin >> xo;
        if (xo == 'x' || xo == 'X') {
            notvalid = false;
            game.set_current_player(1);
        } else if (xo == 'o' || xo == 'O') {
            notvalid = false;
            game.set_current_player(0);
        } else {
            cout << "Only X and O are allowed, please enter again." << endl;
        }
    }

    // Game loop
    while (game.checkWin() == -2) {
        // Human player's move
        while (true) {
            cout << "Enter row and column (0-2): ";
            cin >> r >> c;
            if (r > 2 || c > 2 || r < 0 || c < 0) {
                cout << "Invalid move, try within the valid spaces." << endl;
            } else if (game.getCellValue(r, c) != '-') {
                cout << "The space is filled, try another one." << endl;
            } else {
                break;
            }
        }

        game.insertTarget(r, c);
        game.displayBoard();
        if (game.checkWin() != -2) break;

        // AI move
        Move aiMove = game.minimax_with_pruning(game, MIN, MAX);
        game.insertTarget(aiMove.row, aiMove.col);
        game.displayBoard();
    }

    // Display the result
    int result = game.checkWin();
    if (result == 1) {
        cout << "Congratulations! Player X wins!" << endl;
    } else if (result == -1) {
        cout << "Congratulations! Player O wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}*/