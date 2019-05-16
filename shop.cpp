#include "shop.h"
#include "ui_shop.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QPushButton>

#include <iostream>


shop::shop(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::shop)
{
    //    ui->setupUi(this);

    QString qry_cmd = "SELECT * FROM products LIMIT 5;";
    QSqlQuery query;
    query.exec(qry_cmd);

//    if ( !db->open() )
//    {
//        QMessageBox::information(this, "", "Can't Connect To Database!");
//    }
//    else
//    {
//        QMessageBox::information(this, "", "Connected");
//    }

    int i = 0;
    QPushButton *test;
    QString name;
    while ( query.next() )
    {
        test = new QPushButton(this), name = query.value("name").toString();
        test->setObjectName(name);
        test->setText(name);
        test->setGeometry(QRect(i*50, i*50, 50, 50));
        i++;
    }

}

shop::~shop()
{
    delete ui;
}
