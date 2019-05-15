#include "authentication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite3");
    db.open();

    Authentication auth(nullptr, &db);
    auth.show();



    return a.exec();
}
