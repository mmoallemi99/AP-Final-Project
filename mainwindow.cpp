#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "product.h"
#include "ui_new_product.h"

#include <QtSql>
#include <QSqlTableModel>
#include <QTableView>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite3");
    db.open();

    ui->setupUi(this);

    if ( !db.open() )
    {
        ui->db_status->setText("Can't Connect To Database!");
    }
    else
    {
        ui->db_status->setText("Connected");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_new_product_clicked()
{
    Product new_product;
    new_product.show();
    new_product.exec();
}


void MainWindow::on_search_clicked()
{
    QString search_input = ui->search_input->text();
    QString selected_type = ui->type_select->currentText();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("products");

    QString filter = "name LIKE '%%1%' AND type='%2'";
    filter = filter.arg(search_input, selected_type);
    model->setFilter(filter);
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}









