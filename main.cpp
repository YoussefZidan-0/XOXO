#include "mainwindow.h"
#include "board.h"
#include <QApplication>
// char current_player=1; // 1 for 'X', 0 for 'O'

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
