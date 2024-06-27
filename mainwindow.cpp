#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "DatabaseManager.h"
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

    if (!DatabaseManager::instance().connectToDatabase()) {
        qDebug() << "Failed to open the database";
    } else {
        qDebug() << "Connected to database";
    }

    // Display the initial state of the Tic Tac Toe board
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionexit_triggered() {
    close();
}

void MainWindow::on_lineEdit_returnPressed() {
    // Implement functionality if needed
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1) {
    // Implement functionality if needed
}

void MainWindow::on_commandLinkButton_clicked() {
    hide();
    pastgames = new HistoryDialog(this);
    pastgames->show();
}

void MainWindow::on_actionPast_Games_triggered() {
    if (pastgames == nullptr) {
        pastgames = new HistoryDialog(this);
    }
    pastgames->show();
}

void MainWindow::on_pushButton_10_clicked() {
    QString username = ui->username->text();
    QString password = ui->password->text();

    if (login(username, password)) {
        QMessageBox::information(this, "Login", "Login successful!");
    } else {
        QMessageBox::warning(this, "Login", "Login failed. Invalid username or password.");
    }
}

void MainWindow::on_pushButton_11_clicked() {
    QString username = ui->username->text();
    QString password = ui->password->text();

    if (signup(username, password)) {
        QMessageBox::information(this, "Sign Up", "Sign up successful! You can now log in.");
    } else {
        QMessageBox::warning(this, "Sign Up", "Sign up failed. Please check your details and try again.");
    }
}

void MainWindow::on_signupButton_clicked() {
    // Implement functionality if needed
}

void MainWindow::on_radioButton_4_toggled(bool checked) {
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        ticTacToeBoard->current_player = 0;
}

void MainWindow::on_radioButton_3_toggled(bool checked) {
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        ticTacToeBoard->current_player = 1;
}

void MainWindow::on_radioButton_toggled(bool checked) {
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        this->AI_mode = true;
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
    if(ticTacToeBoard->Checkstart(*ticTacToeBoard))
        this->AI_mode = false;
}

void MainWindow::resetBoard() {
    ticTacToeBoard->reset();
    for (int i = 0; i < 9; ++i) {
        int row = i / 3;
        int col = i % 3;
        QWidget *widget = ui->gridLayout_2->itemAtPosition(row, col)->widget();
        QPushButton *button = qobject_cast<QPushButton*>(widget);
        if (button) {
            button->setText("");
        }
    }

    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(true);

    ui->radioButton->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton->setAutoExclusive(true);
    ui->radioButton_2->setAutoExclusive(true);
}

void MainWindow::handleButtonClick(int row, int col) {
    if (ticTacToeBoard->board[row][col] != '-') {
        return;
    }

    ticTacToeBoard->insertTarget(row, col);
    ticTacToeBoard->displayBoard();
    QWidget *widget = ui->gridLayout_2->itemAtPosition(row, col)->widget();
    QPushButton *button = qobject_cast<QPushButton*>(widget);

    if (button) {
        char cellValue = ticTacToeBoard->getCellValue(row, col);
        button->setText(cellValue == '1' ? "X" : "O");
    }

    int result = ticTacToeBoard->checkWin();
    if (result != -2) {
        displayGameResult(result);
        recordGameHistory(result);
        return;
    }

    if (AI_mode) {
        Move aiMove = ticTacToeBoard->minimax_with_pruning(*ticTacToeBoard);
        ticTacToeBoard->insertTarget(aiMove.row, aiMove.col);
        ticTacToeBoard->displayBoard();

        QWidget *widget2 = ui->gridLayout_2->itemAtPosition(aiMove.row, aiMove.col)->widget();
        QPushButton *button2 = qobject_cast<QPushButton*>(widget2);

        if (button2) {
            char cellValue = ticTacToeBoard->getCellValue(aiMove.row, aiMove.col);
            button2->setText(cellValue == '0' ? "O" : "X");
        }

        result = ticTacToeBoard->checkWin();
        if (result != -2) {
            displayGameResult(result);
            recordGameHistory(result);
            return;
        }
    }
}

void MainWindow::displayGameResult(int result) {
    QString message;
    if (result == 1) {
        message = "Player X wins!\nلاعب X يفوز";
    } else if (result == 0) {
        message = "It's a draw!\nتعادل";
    } else if (result == -1) {
        message = "Player O wins!\nلاعب O يفوز";
    }
    QMessageBox::information(this, "Game Over", message);
    resetBoard();
}

bool MainWindow::login(const QString &username, const QString &password) {
    if (DatabaseManager::instance().userExists(username, password)) {
        return true;
    }
    return false;
}

bool MainWindow::signup(const QString &username, const QString &password) {
    if (!DatabaseManager::instance().userExists(username, QString())) {
        return DatabaseManager::instance().addUser(username, password);
    }
    return false;
}

void MainWindow::recordGameHistory(int result) {
    QSqlDatabase mydb = QSqlDatabase::database();
    if (!mydb.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QString winner;
    if (result == 1) {
        winner = "Player X";
    } else if (result == 0) {
        winner = "Draw";
    } else if (result == -1) {
        winner = "Player O";
    }

    QSqlQuery query;
    query.prepare("INSERT INTO games (date, winner) VALUES (:date, :winner)");
    query.bindValue(":date", QDateTime::currentDateTime().toString());
    query.bindValue(":winner", winner);

    if (!query.exec()) {
        qDebug() << "Error adding game to history: " << query.lastError().text();
    }
}
