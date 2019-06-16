#include "index.h"
#include "ui_index.h"

#include "product.h"
#include "shop.h"

#include "credit_manager.h"

#include "user.h"

#include <QtSql>
#include <QSqlTableModel>
#include <QTableView>

#include <QGridLayout>

index::index(QWidget *parent, QSqlDatabase *db, class user *user):
    QDialog(parent),
    ui(new Ui::index)
{
    this->db = *db;
    ui->setupUi(this);

    this->user = user;

    ui->logged_in_user->setText(user->get_username());


    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user->get_username());
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

    QLineEdit *search = ui->search_input;
    connect(search, SIGNAL(textChanged(const QString &)), this, SLOT(on_search_clicked()));


    if ( user->get_is_admin() == 0 )
    {
        QCommandLinkButton *credit_manager = new QCommandLinkButton;
        credit_manager->setObjectName("credit_manager");
        credit_manager->setText("Charge Account / Redeem Coupon");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(credit_manager->sizePolicy().hasHeightForWidth());
        credit_manager->setSizePolicy(sizePolicy);

        ui->buttons_box->addWidget(credit_manager);

        connect(credit_manager, SIGNAL(clicked()), this, SLOT(on_credit_manager_clicked()));
    }
    else
    {
        QCommandLinkButton *new_product = new QCommandLinkButton;
        new_product->setObjectName("new_product");
        new_product->setText("New Product");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(new_product->sizePolicy().hasHeightForWidth());
        new_product->setSizePolicy(sizePolicy);

        ui->buttons_box->addWidget(new_product);

        connect(new_product, SIGNAL(clicked()), this, SLOT(on_new_product_clicked()));
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

    QString filter = "\"%1\" LIKE '%%2%'";
    filter = filter.arg(search_by, search_input);
    model->setFilter(filter);
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}


void index::on_all_products_clicked()
{
    shop all_products(this, user);
    all_products.show();
    all_products.exec();
}

void index::on_credit_manager_clicked()
{
    credit_manager crdt(this, user->get_username());
    crdt.show();
    crdt.exec();

    QSqlQuery query;
    QString qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user->get_username());
    query.prepare(qry_cmd);
    query.exec();
    query.next();
    this->ui->user_credit->setText(query.value(0).toString());
}
