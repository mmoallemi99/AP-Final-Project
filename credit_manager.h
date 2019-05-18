#ifndef CREDIT_MANAGER_H
#define CREDIT_MANAGER_H

#include <QDialog>
#include <QMap>
#include <QString>

namespace Ui {
class credit_manager;
}

class credit_manager : public QDialog
{
    Q_OBJECT

public:
    explicit credit_manager(QWidget *parent = 0, QString user = nullptr);
    ~credit_manager();

private slots:

    void on_charge_credit_clicked();

    void on_redeem_coupon_clicked();

private:
    Ui::credit_manager *ui;
    QMap<QString, int> coupons;
};

#endif // CREDIT_MANAGER_H
