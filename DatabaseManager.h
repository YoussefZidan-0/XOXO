#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool connectToDatabase();
    bool userExists(const QString& username, const QString& password = QString());
    bool addUser(const QString& username, const QString& password);

private:
    DatabaseManager();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
