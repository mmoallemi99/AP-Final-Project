#ifndef USER_H
#define USER_H

#include <QString>
#include <QMap>
#include <QVariant>


class user : public QVariant
{

public:
    user(QString username);

    static bool sign_up(QString username, QString password);
    static QString login(QString username, QString password);

    QString get_username();
    int get_credit();
    int get_is_admin();

private:
    QString username;
    QString password;
    int credit;
    int is_admin=0;


};

#endif // USER_H
