#include "index.h"
#include "ui_index.h"

#include "product.h"
#include "shop.h"

#include <QtSql>
#include <QSqlTableModel>
#include <QTableView>

index::index(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::index)
{
    this->db = *db;
    ui->setupUi(this);

    if ( !db->open() )
    {
        ui->db_status->setText("Can't Connect To Database!");
    }
    else
    {
        ui->db_status->setText("Connected");
    }
}

index::~index()
{
    delete ui;
}

void index::on_new_product_clicked()
{
    Product new_product;
    new_product.show();
    new_product.exec();
}


void index::on_search_clicked()
{
    QString search_input = ui->search_input->text();
    QString search_by = ui->search_by->currentText();

    if ( search_by == "-----" )
    {
        QMessageBox::information(this, "Field Required", "Please Select What You Want To Search By");
        return;
    }
    else if ( search_input == "" )
    {
        QMessageBox::information(this, "Field Required", "Please Type Search Text");
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("products");

    QString filter = "%1 LIKE '%%2%'";
    filter = filter.arg(search_by, search_input);
    model->setFilter(filter);
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}


void index::on_all_products_clicked()
{
    shop all_products(this, &(this->db));
    all_products.show();
    all_products.exec();
}
