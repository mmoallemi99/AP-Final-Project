#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>


namespace Ui {

class Product;
}

class Product : public QDialog
{
    Q_OBJECT

public:
    explicit Product(QWidget *parent = nullptr);
    ~Product();

private slots:
    void on_add_product_clicked();

private:
    Ui::Product *ui;

    QString name;
    QString country;
    QString type;
    QString description;
    long long int price;
    long int stock_available;
};


#endif // PRODUCT_H







