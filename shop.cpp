#include "shop.h"
#include "ui_shop.h"

#include <QSqlQuery>
#include <QMessageBox>

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include <QMap>
#include <QVector>

#include <QSqlTableModel>
#include <QTableView>


shop::shop(QWidget *parent, QSqlDatabase *db, QString user) :
    QDialog(parent),
    ui(new Ui::shop)
{
    //    ui->setupUi(this);

    QString qry_cmd = "SELECT * FROM products;";
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


    QLabel *new_name_label;
    QLabel *new_type_label;
    QLabel *new_price_label;
    QLabel *new_available_label;
    QPushButton *new_buy;
    QPushButton *new_delete;
    QPushButton *new_edit;

    QMap<QString, QString> product_dict;

    QWidget *all_products_widget = new QWidget(this);
    all_products_widget->setObjectName(QStringLiteral("formLayoutWidget"));
    all_products_widget->setGeometry(QRect(60, 20, 1024, 512));
    QGridLayout *all_products_grid = new QGridLayout(all_products_widget);
    all_products_grid->setObjectName(QStringLiteral("formLayout"));
    all_products_grid->setContentsMargins(0, 0, 0, 0);


    new_name_label = new QLabel(this);
    new_type_label = new QLabel(this);
    new_price_label = new QLabel(this);
    new_available_label = new QLabel(this);


    new_name_label->setObjectName("name_header");
    new_name_label->setText("Product Name");
    all_products_grid->addWidget(new_name_label, 1, 0, 2, 2);

    new_type_label->setObjectName("type_header");
    new_type_label->setText("Product Type");
    all_products_grid->addWidget(new_type_label, 1, 1, 2, 2);

    new_price_label->setObjectName("price_header");
    new_price_label->setText("Product Price");
    all_products_grid->addWidget(new_price_label, 1, 2, 2, 2);

    new_available_label->setObjectName("avilable_header");
    new_available_label->setText("Stock Available");
    all_products_grid->addWidget(new_available_label, 1, 3, 2, 2);


    int i = 2;

    while ( query.next() )
    {
        new_name_label = new QLabel(this);
        new_type_label = new QLabel(this);
        new_price_label = new QLabel(this);
        new_available_label = new QLabel(this);

        new_buy = new QPushButton(this);
        new_delete = new QPushButton(this);
        new_edit = new QPushButton(this);

        product_dict["name"] = query.value("name").toString();
        product_dict["country"] = query.value("country").toString();
        product_dict["type"] = query.value("type").toString();
        product_dict["price"] = query.value("price").toString();
        product_dict["stock_available"] = query.value("stock_available").toString();

        new_name_label->setObjectName(product_dict["name"] + "_name");
        new_name_label->setText(product_dict["name"]);
        all_products_grid->addWidget(new_name_label, i, 0, 1, 1);


        new_type_label->setObjectName(product_dict["name"] + "_type");
        new_type_label->setText(product_dict["type"]);
        all_products_grid->addWidget(new_type_label, i, 1, 1, 1);

        new_price_label->setObjectName(product_dict["name"] + "_price");
        new_price_label->setText(product_dict["price"]);
        all_products_grid->addWidget(new_price_label, i, 2, 1, 1);

        new_available_label->setObjectName(product_dict["name"] + "_available");
        new_available_label->setText(product_dict["stock_available"]);
        all_products_grid->addWidget(new_available_label, i, 3, 1, 1);



        new_buy->setObjectName(product_dict["name"] + "_buy");
        new_buy->setText("buy");
        all_products_grid->addWidget(new_buy, i, 6, 1, 1);
        connect(new_buy, SIGNAL(clicked()), this, SLOT (item_buy()));

        new_edit->setObjectName(product_dict["name"] + "_edit");
        new_edit->setText("edit");
        all_products_grid->addWidget(new_edit, i, 5, 1, 1);
        connect(new_edit, SIGNAL(clicked()), this, SLOT (item_edit()));

        new_delete->setObjectName(product_dict["name"] + "_delete");
        new_delete->setText("delete");
        all_products_grid->addWidget(new_delete, i, 4, 1, 1);
        connect(new_delete, SIGNAL(clicked()), this, SLOT(item_delete()));

        i++;
    }

    QLabel *username_label= new QLabel;
    username_label->setObjectName("username_label");
    username_label->setText(user);
    all_products_grid->addWidget(username_label, i, 2, 1, 1);

    qry_cmd = "SELECT credit FROM users WHERE username='%1';";
    qry_cmd = qry_cmd.arg(user);
    query.prepare(qry_cmd);
    query.exec();
    query.next();

    user_credit = query.value(0).toInt();

    QLabel *credit_label = new QLabel;
    credit_label->setObjectName("credit_label");
    credit_label->setText(QString::number(user_credit));
    all_products_grid->addWidget(credit_label, i, 4, 1, 1);
}

shop::~shop()
{
    delete ui;
}

bool shop::item_buy()
{
    QObject *sender = this->sender();
    QString user = sender->parent()->findChild<QLabel *>("username_label")->text();

    QString item_name = sender->objectName();
    int name_length = item_name.length();
    item_name = item_name.remove(name_length - 4, name_length);

    QLabel *available_label = sender->parent()->findChild<QLabel *>(item_name + "_available");
    long int item_available = available_label->text().toLong();

    if ( item_available == 0 )
    {
        QMessageBox::information(this, "Can't Buy :(", "Sorry This Item Is Out of Stock!");
        return false;
    }

    QLabel *price_label = sender->parent()->findChild<QLabel *>(item_name + "_price");
    long long int item_price = price_label->text().toLongLong();

    QLabel *current_credit_label = sender->parent()->findChild<QLabel *>("credit_label");

    if ( user_credit < item_price )
    {
        QMessageBox::information(this, "Not Enough Credit!", "Sorry But You Don't Have Enough Credits For This Item\n"
                                                             "You Can Close This Page & Charge Your Account From Main Menu");
        return false;
    }

    item_available -= 1;

    QSqlQuery query;
    QString qry_cmd = "UPDATE products SET stock_available='%1' WHERE name='%2';";
    qry_cmd = qry_cmd.arg(QString::number(item_available), item_name);
    query.exec(qry_cmd);



    user_credit -= item_price;


    qry_cmd = "UPDATE users SET credit='%1' WHERE username='%2';";
    qry_cmd = qry_cmd.arg(QString::number(user_credit), user);
    query.prepare(qry_cmd);
    query.exec();

    available_label->setText(QString::number(item_available));
    current_credit_label->setText(QString::number(user_credit));

    QString success_msg = "You Bought %1 And It Cost You %2";
    success_msg = success_msg.arg(item_name, QString::number(item_price));
    QMessageBox::information(this, "Success!", success_msg);
    return true;
}

void shop::item_edit()
{
    QObject *sender = this->sender();

    QString item_name = sender->objectName();
    int name_length = item_name.length();
    item_name = item_name.remove(name_length - 5, name_length);

    QSqlTableModel *table_model = new QSqlTableModel(this, this->db);
    table_model->setTable("products");

    QString filter = "name LIKE '%1';";
    filter = filter.arg(item_name);
    table_model->setFilter(filter);
    table_model->select();

    QTableView *table_view = new QTableView;
    table_view->setModel(table_model);
    table_view->show();

}

bool shop::item_delete()
{
    QObject *sender = this->sender();

    QString item_name = sender->objectName();
    int name_length = item_name.length();
    item_name = item_name.remove(name_length - 7, name_length);

    QSqlQuery query;
    QString qry_cmd = "DELETE FROM products WHERE name='%1';";
    qry_cmd = qry_cmd.arg(item_name);

    query.prepare(qry_cmd);
    if ( !query.exec() )
    {
        QString msg = "A Problem Occured While Trying To Delete Item: %1";
        msg = msg.arg(item_name);
        QMessageBox::information(this, "Failed!", msg);
        return false;
    }


    QLabel *name_label = this->findChild<QLabel *>(item_name + "_name");
    QLabel *type_label = this->findChild<QLabel *>(item_name + "_type");
    QLabel *price_label = this->findChild<QLabel *>(item_name + "_price");
    QLabel *available_label = this->findChild<QLabel *>(item_name + "_available");

    QPushButton *buy_button = this->findChild<QPushButton *>(item_name + "_buy");
    QPushButton *delete_button = this->findChild<QPushButton *>(item_name + "_delete");
    QPushButton *edit_button = this->findChild<QPushButton *>(item_name + "_edit");

    delete name_label;
    delete type_label;
    delete price_label;
    delete available_label;
    delete buy_button;
    delete delete_button;
    delete edit_button;

    return true;
}





