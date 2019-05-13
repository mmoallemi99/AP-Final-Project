#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "product.h"
#include "ui_new_product.h"

#include <QtSql>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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
    Product form;
    form.show();
    form.exec();
}
