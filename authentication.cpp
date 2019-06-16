#include "authentication.h"
#include "ui_authentication.h"

#include "index.h"

#include "user.h"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlTableModel>
#include <QMessageBox>

#include <QDebug>

Authentication::Authentication(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::Authentication)
{
    ui->setupUi(this);

    this->db = *db;

    if ( !db->isOpen() )
    {
        QMessageBox::information(this, "Connection is ....ed Up!", "");
        return;
    }

    QString qry_cmd = "CREATE TABLE users (username varchar(30) primary key,"
                      "password varchar(100),"
                      "credit int,"
                      "is_admin int);";
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

    QString log_in_result = user::login(entered_username, entered_password);

    if ( log_in_result == "ok")
    {
        user *user_logged_in = new user(entered_username);
        class index index(nullptr, &(this->db), user_logged_in);
        index.show();
        index.exec();
    }
    else
    {
        QMessageBox::information(this, "Login Failed", log_in_result);
    }


}

void Authentication::on_sign_up_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    bool is_admin = ui->seller_box->checkState();

    bool status = user::sign_up(username, password, is_admin);

    if ( status )
    {
        QMessageBox::information(this, "Registration Message", "You Have Registered Successfully!\nNow You Can Login");
        Authentication::on_login_clicked();
    }
    else
    {
        QMessageBox::information(this, "Registration Message", "Username Exists!\nPlease Use Another Username!");
    }
}







