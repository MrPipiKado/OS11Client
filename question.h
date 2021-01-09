#ifndef QUESTION_H
#define QUESTION_H
#include <QDialog>
#include "globals.h"
#include <netinet/in.h>
#include <arpa/inet.h>
namespace Ui {
class question;
}

class question : public QDialog
{
    Q_OBJECT

public:
    explicit question(QString ip_add, QWidget *parent = nullptr);
    ~question();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::question *ui;
    int sockfd;
    struct sockaddr_in server_addr;
    char name[32];
    char server_ip[15];
};

#endif // QUESTION_H
