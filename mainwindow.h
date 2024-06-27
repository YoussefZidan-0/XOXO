#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include "historydialog.h"
#include "board.h"
#include "DatabaseManager.h"

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
    bool AI_mode;

private slots:
    void on_actionexit_triggered();
    void on_lineEdit_returnPressed();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_commandLinkButton_clicked();
    void on_actionPast_Games_triggered();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_signupButton_clicked();
    void resetBoard();
    void handleButtonClick(int row, int col);
    void on_radioButton_4_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void displayGameResult(int result);
    bool login(const QString &username, const QString &password);
    bool signup(const QString &username, const QString &password);

private:
    void recordGameHistory(int result);
    Ui::MainWindow *ui;
    HistoryDialog *pastgames;
    Board *ticTacToeBoard;
};

#endif // MAINWINDOW_H
