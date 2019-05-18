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
    explicit shop(QWidget *parent = 0, QSqlDatabase *db = nullptr, QString user = nullptr);
    ~shop();
private slots:
    bool item_buy();
    void item_edit();
    bool item_delete();

private:
    Ui::shop *ui;
    QSqlDatabase db;
    int user_credit;
};

#endif // SHOP_H
