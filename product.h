#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#define products_file "products_file.txt"

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
};


#endif // PRODUCT_H







