#include "product.h"
#include "ui_new_product.h"

#include <QString>
#include <QTextEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QtSql>
#include <QObject>
#include <QSqlDatabase>

Product::Product(QWidget *parent, QSqlDatabase *db):
    QDialog(parent),
    ui(new Ui::Product)
{

    ui->setupUi(this);

    QString qry_cmd = "CREATE TABLE products (name varchar(30) primary key, "
                      "country varchar(30),"
                      "type varchar(30),"
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
    name = this->ui->name_input->text();
    country = this->ui->name_input->text();
    type = this->ui->type_select->currentText();
    description = this->ui->description_input->toPlainText();
    price = this->ui->price_input->text().toLongLong();
    stock_available = this->ui->stock_available_input->text().toLong();

    QSqlQuery query;
    QString qry_cmd = "INSERT INTO main.products(name, country, type, description, price, stock_available)"
                      "VALUES ('%1', '%2', '%3', '%4', '%5', '%6');";
    qry_cmd = qry_cmd.arg(name, country, type, description, QString::number(price), QString::number(stock_available));
    query.prepare(qry_cmd);
    if ( query.exec() )
    {
        QMessageBox::information(this, "Success!", "Product Added Successfully!");
    }
}


