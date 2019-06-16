#include "user.h"

#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>

#include <QSqlRecord>

user::user(QString username)
{
    QString password;

    QString qry_cmd = "SELECT * FROM users WHERE username='%1'";
    qry_cmd = qry_cmd.arg(username);
    QSqlQuery query;
    query.exec(qry_cmd);
    query.next();

    QSqlRecord record = query.record();

    this->username = username;
    this->credit = record.value("credit").toInt();
    this->is_admin = record.value("is_admin").toInt();
}

bool user::sign_up(QString username, QString password)
{
    QString hashed_password;
    hashed_password = QString(QCryptographicHash::hash((password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString qry_cmd = "INSERT INTO users(username, password, credit, is_admin) "
                      "values(:username, :password, :credit, :is_admin);";
    QSqlQuery query;
    query.prepare(qry_cmd);
    query.bindValue(":username", username);
    query.bindValue(":password", hashed_password);
    query.bindValue(":credit", 0);
    query.bindValue(":is_admin", 0);

    return query.exec();
}

QString user::login(QString entered_username, QString entered_password)
{
    QString hashed_password;
    hashed_password = QString(QCryptographicHash::hash((entered_password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString qry_cmd = "SELECT * FROM users WHERE username='%1'";
    qry_cmd = qry_cmd.arg(entered_username);
    QSqlQuery query;
    query.exec(qry_cmd);

    if ( !query.next() )
    {
        return "User Does Not Exist \n Register Now!";
    }

    QString username = query.value("username").toString();
    if ( username == entered_username )
    {
        QString hashed_password;
        hashed_password = QString(QCryptographicHash::hash((entered_password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

        QString password = query.value("password").toString();

        if ( hashed_password == password )
        {
            return "ok";
        }
        else
        {
            return "Wrong Username or Password! \n Please Try Again!";
        }
    }
    return "ok";
}

QString user::get_username()
{
    return username;
}

int user::get_credit()
{
    return credit;
}

int user::get_is_admin()
{
    return is_admin;
}

