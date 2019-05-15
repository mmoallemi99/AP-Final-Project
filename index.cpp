#include "index.h"
#include "ui_index.h"

#include "product.h"

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


void index::on_all_products_clicked()
{

}
