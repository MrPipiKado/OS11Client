#include "username_password.h"
#include "ui_username_password.h"

QString username;
QString password;

username_password::username_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::username_password)
{
    ui->setupUi(this);
}

username_password::~username_password()
{
    delete ui;
}

void username_password::on_pushButton_clicked()
{
    username = ui->lineEdit->text();
    password = ui->lineEdit_2->text();
    done(1);
}

void username_password::on_pushButton_2_clicked()
{
    done(0);
}
