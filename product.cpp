#include "product.h"
#include "ui_new_product.h"

#include <QString>
#include <QTextEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QtSql>
#include <QObject>


Product::Product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);

    QString qry_cmd = "CREATE TABLE products (name varchar(20) primary key,"
                      "description varchar(300),"
                      "price int,"
                      "stock_available int);";
    QSqlQuery query;
    query.prepare(qry_cmd);
    query.exec();
}

Product::~Product()
{
    delete ui;
}

void Product::on_add_product_clicked()
{
    QString name = this->ui->name_input->text();
    QString description = this->ui->description_input->toPlainText();
    long long int price = this->ui->price_input->text().toLongLong();
    long int stock_available = this->ui->stock_available_input->text().toLong();

    QSqlQuery query;
    QString qry_cmd = "INSERT INTO main.products(name, description, price, stock_available)"
                      "VALUES ('%1', '%2', '%3', '%4');";
    qry_cmd = qry_cmd.arg(name, description, QString::number(price), QString::number(stock_available));
    query.prepare(qry_cmd);
    query.exec();
}


