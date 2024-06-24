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
    if (!ticTacToeBoard->isCellEmptyPublic(row, col)) {
        // QMessageBox::information(this, "Invalid Move", "This cell is already taken. Please choose another cell.");
        return; // Exit the function if cell is not empty
    }

    // Player move
    ticTacToeBoard->insertTarget(row, col);
    ticTacToeBoard->displayBoard();
    QWidget *widget = ui->gridLayout_2->itemAtPosition(row, col)->widget();
    QPushButton *button = qobject_cast<QPushButton*>(widget);

    if (button) {
        char cellValue = ticTacToeBoard->getCellValue(row, col);
        button->setText(QString(cellValue));
    }

    int result = ticTacToeBoard->checkWin();
    if (result != -2) {
        // If the game is over, display the result
        displayGameResult(result);
        return;
    }

    if (AI_mode) {
        // AI move

        Move aiMove = ticTacToeBoard->minimax_with_pruning(*ticTacToeBoard);
        ticTacToeBoard->insertTarget(aiMove.row, aiMove.col);
        ticTacToeBoard->displayBoard();

        QWidget *widget2 = ui->gridLayout_2->itemAtPosition(aiMove.row, aiMove.col)->widget();
        QPushButton *button2 = qobject_cast<QPushButton*>(widget2);

        if (button2) {
            char cellValue = ticTacToeBoard->getCellValue(aiMove.row, aiMove.col);
            button2->setText(QString(cellValue));
        }

        result = ticTacToeBoard->checkWin();
        if (result != -2) {
            // If the game is over, display the result
            displayGameResult(result);
            return;
        }
    }
}


void MainWindow::displayGameResult(int result)
{
    if (result == 1) {
        QMessageBox::information(this, "Game Over", "Player X wins!");
    } else if (result == 0) {
        QMessageBox::information(this, "Game Over", "Player O wins!");
    } else if (result == -1) {
        QMessageBox::information(this, "Game Over", "It's a draw!");
    }
    resetBoard();
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
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);

    // Uncheck the radio buttons
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
/*
 *
 * reset the radio buttons to their default state of AI and PVP
    // Re-enable mutual exclusivity
    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(true);

    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);

// Uncheck the radio buttons
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);

// Re-enable mutual exclusivity
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(true);*/
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
    pastgames=new HistoryDialog(this);
    pastgames->show();
}


void MainWindow::on_pushButton_10_clicked()//login
{

    auto username=ui->username->text();
    auto password=ui->password->text();
    if(username=="test" && password=="test")
        qDebug()<<"loggedin success";
}


void MainWindow::on_pushButton_11_clicked()//signup
{


}


void MainWindow::on_actionexit_triggered()
{
    close();
}


void MainWindow::on_radioButton_4_toggled(bool checked) //start player o
{

if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        ticTacToeBoard->current_player=0;

}


void MainWindow::on_radioButton_3_toggled(bool checked)//start player x
{
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        ticTacToeBoard->current_player=1;


}

void MainWindow::on_radioButton_toggled(bool checked){
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        this->AI_mode = true;
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        this->AI_mode = false;

}
