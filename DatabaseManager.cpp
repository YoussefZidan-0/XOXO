#include "DatabaseManager.h"
#include <QDebug>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("userdb.sqlite");
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectToDatabase() {
    if (!db.open()) {
        qWarning() << "Error opening database connection:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, wins INTEGER DEFAULT 0, draws INTEGER DEFAULT 0, losses INTEGER DEFAULT 0, password TEXT, game_counter INTEGER DEFAULT 0)")) {
        qWarning() << "Error creating users table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::userExists(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        if (password.isEmpty()) {
            return true;
        } else {
            QString storedPassword = query.value(0).toString();
            QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
            return storedPassword == hashedPassword;
        }
    }
    return false;
}

bool DatabaseManager::addUser(const QString& username, const QString& password) {
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (query.exec()) {
        return true;
    } else {
        qWarning() << "Error inserting data:" << query.lastError().text();
        return false;
    }
}
