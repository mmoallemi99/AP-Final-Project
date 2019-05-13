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
    // My Product Info Vars
    QString name;
    QString description;
    unsigned long int price;
    unsigned int stock_available;

    bool add_new(QString name, QString description, long long int price, long int stock_available)
    {
        QFile file(products_file);
        file.open(QFile::Text|QFile::WriteOnly|QFile::Append);
        if ( !file.isOpen() )
        {
            QMessageBox::information(this, "NaH lol :)", "ok");
        }
        QTextStream texts(&file);

        texts << name << ", ";
        texts << description << ", ";
        texts << price << ", ";
        texts << stock_available << ", ";
        texts << endl;
        file.flush();
        file.close();
        return true;
    }
};


#endif // PRODUCT_H







