#ifndef SHOP_H
#define SHOP_H

#include "user.h"

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class shop;
}

class shop : public QDialog
{
    Q_OBJECT

public:
    explicit shop(QWidget *parent = nullptr, user *user = nullptr);
    ~shop();
private slots:
    bool item_buy();
    void item_edit();
    bool item_delete();

private:
    Ui::shop *ui;
     QSqlDatabase db;
    int user_credit;
    class user *user;
};

#endif // SHOP_H
