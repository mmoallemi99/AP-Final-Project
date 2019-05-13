#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <iostream>

class DatabaseManager : public QObject

{
public:
    DatabaseManager(QObject *parent = nullptr){}
    ~DatabaseManager(){}

public:
    bool openDB()
    {


        return true;

    }

    int addProduct(QString name, QString description, long long int price, long int stock_available)
    {

        int newId = -1;
        bool ret = false;

        if (db.isOpen())
        {
            std::cout << "ok" << std::endl;

            ret = query.exec();
            // Get database given autoincrement value
            if (ret)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                newId = query.lastInsertId().toInt();
            }
        }
        else {
            std::cout << "NOT ok" << std::endl;
        }
        return newId;
    }

private:
    QSqlDatabase db;
};


#endif // DATABASEMANAGER_H
