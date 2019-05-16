#include "authentication.h"
#include "ui_authentication.h"

#include "index.h"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlTableModel>
#include <QDebug>

#include <QMessageBox>


Authentication::Authentication(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);

    this->db = *db;


    if ( !db->isOpen() )
        QMessageBox::information(this, "Connection is ....ed Up!", "");

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
    QString entered_username = ui->username->text();
    QString entered_password = ui->password->text();

    QString hashed_password;
    hashed_password = QString(QCryptographicHash::hash((entered_password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString qry_cmd = "SELECT * FROM users WHERE username='%1'";
    qry_cmd = qry_cmd.arg(entered_username);
    QSqlQuery query;
    query.exec(qry_cmd);

    if ( !query.next() )
    {
        QMessageBox::information(this, "Login Failed", "User Does Not Exist \n Register Now!");
        return;
    }

    QString username = query.value("username").toString();

    if ( username == entered_username )
    {
        QString hashed_password;
        hashed_password = QString(QCryptographicHash::hash((entered_password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

        QString password = query.value("password").toString();
        if ( hashed_password == password )
        {
            class index index(nullptr, &(this->db));
            index.show();
            index.exec();
        }
    }

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
        QMessageBox::information(this, "Registration Message", "Wrong Username or Password! \n Please Try Again!");
    }
}







