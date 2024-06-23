#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"historydialog.h"
#include "board.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_actionexit_triggered();

   // void on_radioButton_3_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_commandLinkButton_clicked();

    void on_actionPast_Games_triggered();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void resetBoard();
     void handleButtonClick(int row,int col);

private:
    Ui::MainWindow *ui;
    HistoryDialog *pastgames;
    Board *ticTacToeBoard;
};
#endif // MAINWINDOW_H
