#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Authentication;
}

class Authentication : public QDialog
{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent = nullptr);
    ~Authentication();

private slots:
    void on_login_clicked();
    void on_sign_up_clicked();

private:
    Ui::Authentication *ui;
    QSqlDatabase db;


};

#endif // AUTHENTICATION_H
