#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "historydialog.h"
#include "board.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the Tic Tac Toe board
    ticTacToeBoard = new Board();

    // Connect each push button to a slot
    connect(ui->pushButton_0, &QPushButton::clicked, this, [this]() { handleButtonClick(0, 0); });
    connect(ui->pushButton_1, &QPushButton::clicked, this, [this]() { handleButtonClick(0, 1); });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() { handleButtonClick(0, 2); });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() { handleButtonClick(1, 0); });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() { handleButtonClick(1, 1); });
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() { handleButtonClick(1, 2); });
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() { handleButtonClick(2, 0); });
    connect(ui->pushButton_7, &QPushButton::clicked, this, [this]() { handleButtonClick(2, 1); });
    connect(ui->pushButton_8, &QPushButton::clicked, this, [this]() { handleButtonClick(2, 2); });

    // Display the initial state of the Tic Tac Toe board
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick(int row, int col)
{
    // Check if the cell is already taken
    if (!ticTacToeBoard->isCellEmptyPublic(row, col)) {
        // QMessageBox::information(this, "Invalid Move", "This cell is already taken. Please choose another cell.");
        return; // Exit the function if cell is not empty
    }

    // Get the widget at the specified position in the grid layout
    ticTacToeBoard->insertTarget(row, col);
    QWidget *widget = ui->gridLayout_2->itemAtPosition(row, col)->widget();

    // Check if the widget is a QPushButton
    QPushButton *button = qobject_cast<QPushButton*>(widget);
    if (button) {
        // Change the text displayed in the button
        char cellValue = ticTacToeBoard->getCellValue(row, col);
        button->setText(QString(cellValue));

        // Check if the game is over
        int result = ticTacToeBoard->checkWin();
        if (result == 1) {
            // Player X wins
            QMessageBox::information(this, "Game Over", "Player X wins!");
            resetBoard(); // Reset the board
        } else if (result == 0) {
            // Player O wins
            QMessageBox::information(this, "Game Over", "Player O wins!");
            resetBoard(); // Reset the board
        } else if (result == -1) {
            // Draw
            QMessageBox::information(this, "Game Over", "It's a draw!");
            resetBoard(); // Reset the board
        }
    } else {
        qDebug() << "Error: Widget is not a QPushButton!";
    }
}

void MainWindow::resetBoard()
{
    // Reset the Tic Tac Toe board
    ticTacToeBoard->reset();

    // Clear the text of each push button
    for (int i = 0; i < 9; ++i) {
        // Calculate row and column indices from button index
        int row = i / 3;
        int col = i % 3;

        // Get the widget at the specified position in the grid layout
        QWidget *widget = ui->gridLayout_2->itemAtPosition(row, col)->widget();

        // Check if the widget is a QPushButton
        QPushButton *button = qobject_cast<QPushButton*>(widget);
        if (button) {
            button->setText("");
        }
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
}

void MainWindow::on_actionPast_Games_triggered()
{
}

void MainWindow::on_commandLinkButton_clicked()
{
    hide();
    pastgames = new HistoryDialog(this);
    pastgames->show();
}

void MainWindow::on_pushButton_10_clicked() // login
{
    auto username = ui->username->text();
    auto password = ui->password->text();
    if (username == "test" && password == "test")
        qDebug() << "loggedin success";
}

void MainWindow::on_pushButton_11_clicked() // signup
{
}

void MainWindow::on_actionexit_triggered()
{
    close();
}

void MainWindow::on_radioButton_4_clicked() // Slot for O button
{
    ticTacToeBoard->current_player = 0; // Set current player to O
}

void MainWindow::on_radioButton_3_clicked() // Slot for X button
{
    ticTacToeBoard->current_player = 1; // Set current player to X
}
