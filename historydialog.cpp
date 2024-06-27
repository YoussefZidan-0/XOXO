#include "historydialog.h"
#include "ui_historydialog.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

HistoryDialog::HistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);

    // Fetch the game history from the database
    QSqlDatabase mydb = QSqlDatabase::database();
    if (!mydb.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, mydb);
    model->setTable("game_history");
    model->select();

    ui->tableView->setModel(model);  // Use tableView instead of tableWidget
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}
