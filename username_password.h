#ifndef USERNAME_PASSWORD_H
#define USERNAME_PASSWORD_H

#include <QDialog>
#include "globals.h"
namespace Ui {
class username_password;
}

class username_password : public QDialog
{
    Q_OBJECT

public:
    explicit username_password(QWidget *parent = nullptr);
    ~username_password();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::username_password *ui;
};

#endif // USERNAME_PASSWORD_H
