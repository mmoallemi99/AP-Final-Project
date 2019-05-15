#ifndef INDEX_H
#define INDEX_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class index;
}

class index : public QDialog
{
    Q_OBJECT

public:
    explicit index(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~index();

private slots:
    void on_new_product_clicked();
    void on_search_clicked();

    void on_all_products_clicked();

private:
    Ui::index *ui;
    QSqlDatabase db;

};

#endif // INDEX_H