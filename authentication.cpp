#include "authentication.h"
#include "ui_authentication.h"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlTableModel>
#include <QDebug>

#include <QMessageBox>


Authentication::Authentication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite3");
    db.open();

    if ( !db.isOpen() )
        QMessageBox::information(this, "well fuck", "");

    QString qry_cmd = "CREATE TABLE users (username varchar(30) primary key,"
                      "password varchar(100));";
    QSqlQuery query;
    query.prepare(qry_cmd);
    query.exec();
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString hashed_password;
    hashed_password = QString(QCryptographicHash::hash((password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString qry_cmd = "SELECT username FROM users WHERE username='%1' FETCH FIRST ROW ONLY";
    qry_cmd = qry_cmd.arg(username);
    QSqlQuery query;
    query.prepare(qry_cmd);
    query.exec();
    QMessageBox::information(this, "Registration Message", "Can Login");
//    if ( query.next() == username )
//    {
//        QMessageBox::information(this, "Registration Message", "Can Login");
//    }

}

void Authentication::on_sign_up_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString hashed_password;
    hashed_password = QString(QCryptographicHash::hash((password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString qry_cmd = "INSERT INTO users(username, password) "
                      "values(:username, :password);";
    QSqlQuery query;
    query.prepare(qry_cmd);
    query.bindValue(":username", username);
    query.bindValue(":password", hashed_password);
    if ( query.exec() )
    {
        QMessageBox::information(this, "Registration Message", "You Have Registered Successfully! \n Now You Can Login");
    }
    else
    {
        QMessageBox::information(this, "Registration Message", "Something Went Wrong :( \n Please Try Again :) ");
    }
}







