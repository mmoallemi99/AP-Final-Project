#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class shop;
}

class shop : public QDialog
{
    Q_OBJECT

public:
    explicit shop(QWidget *parent = 0, QSqlDatabase *db = nullptr);
    ~shop();

private:
    Ui::shop *ui;
    QSqlDatabase db;
};

#endif // SHOP_H
