#include "index.h"
#include "ui_index.h"

#include "product.h"
#include "shop.h"

#include "credit_manager.h"

#include <QtSql>
#include <QSqlTableModel>
#include <QTableView>

index::index(QWidget *parent, QSqlDatabase *db, QString user):
    QDialog(parent),
    ui(new Ui::index)
{
    this->db = *db;
    ui->setupUi(this);
    ui->logged_in_user->setText(user);
    this->user = user;


    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user);
    query.prepare(qry_cmd);
    query.exec();
    query.next();
    ui->user_credit->setText(query.value(0).toString());


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
    shop all_products(this, &(this->db), user);
    all_products.show();
    all_products.exec();
}

void index::on_credit_manager_clicked()
{

    credit_manager crdt(nullptr, user);
    crdt.show();
    crdt.exec();

    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user);
    query.prepare(qry_cmd);
    query.exec();
    query.next();
    this->ui->user_credit->setText(query.value(0).toString());
}
