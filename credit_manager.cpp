#include "credit_manager.h"
#include "ui_credit_manager.h"

#include <QSqlQuery>
#include <QMessageBox>

credit_manager::credit_manager(QWidget *parent, QString user) :
    QDialog(parent),
    ui(new Ui::credit_manager)
{
    ui->setupUi(this);

    coupons["daneshjoo98"] = 500;
    coupons["uisace"] = 1000;
    coupons["ta-ha"] = 2500;
    coupons["asatid"] = 7500;

    ui->logged_in_user->setText(user);

}

credit_manager::~credit_manager()
{
    delete ui;
}

void credit_manager::on_charge_credit_clicked()
{
    QString user = this->ui->logged_in_user->text();

    QString credit_deposit = this->ui->charge_credit_input->text();
    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user);
    query.prepare(qry_cmd);
    query.exec();
    query.next();
    int current_credit = query.value(0).toInt();

    current_credit += credit_deposit.toInt();

    qry_cmd = "UPDATE users SET credit='%1' WHERE username='%2';";
    qry_cmd = qry_cmd.arg(QString::number(current_credit), user);
    query.prepare(qry_cmd);
    query.exec();
    QString success_msg = "You Deposited %1 To Account %2\nCurrent Credit: %3";
    success_msg = success_msg.arg(credit_deposit, user, QString::number(current_credit));
    QMessageBox::information(this, "Success!", success_msg);
}


void credit_manager::on_redeem_coupon_clicked()
{
    QString user = this->ui->logged_in_user->text();
    QString entered_coupon = this->ui->redeem_coupon_input->text();

    if ( !coupons.contains(entered_coupon) )
        QMessageBox::information(this, "Wrong Coupon", "");

    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user);
    query.prepare(qry_cmd);
    query.exec();
    query.next();
    int current_credit = query.value(0).toInt();

    int credit_deposit = coupons.find(entered_coupon).value();

    current_credit += credit_deposit;

    qry_cmd = "UPDATE users SET credit='%1' WHERE username='%2';";
    qry_cmd = qry_cmd.arg(QString::number(current_credit), user);
    query.prepare(qry_cmd);
    query.exec();
    QString success_msg = "You Redeemed Coupon %1 With Value of %2 To Account %3\nCurrent Credit: %4";
    success_msg = success_msg.arg(entered_coupon, QString::number(credit_deposit), user, QString::number(current_credit));
    QMessageBox::information(this, "Success!", success_msg);
}




