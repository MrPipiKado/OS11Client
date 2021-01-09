#include <sys/socket.h>
#include <unistd.h>
int (*socket_connect_)(int, const struct sockaddr *, socklen_t) = connect;
int (*socket_close_)(int) = close;
#include "question.h"
#include "ui_question.h"
#include "globals.h"
#include "username_password.h"
#include <QMessageBox>
question::question(QString ip_add, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::question)
{
    ui->setupUi(this);

    strcpy(server_ip, ip_add.toStdString().c_str());
}

question::~question()
{
    delete ui;
}

void question::on_pushButton_clicked()
{
    username_password form(this);
    if(form.exec())
    {
        char *ip = server_ip;
        char buffer[100];
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_port = htons(9999);


          // Connect to Server
        int err = socket_connect_(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
          if (err == -1) {
                printf("ERROR: connect\n");
            }
        sprintf(buffer, "l %s %s", username.toStdString().c_str(), password.toStdString().c_str());
        send(sockfd, buffer, strlen(buffer), 0);
        char reply[10];
        while(1)
        {
            int receive = recv(sockfd, reply, 10, 0);
            if(receive>0)
            {
                if(reply[0]=='t')
                {
                    socket_close_(sockfd);
                    break;
                }
                if(reply[0]=='f')
                {
                    QMessageBox msgBox(this);
                    msgBox.setText("Log in failed(");
                    msgBox.exec();
                    socket_close_(sockfd);
                    return;
                }
            }
            /*else
            {
                socket_close_(sockfd);
                done(-1);
            }*/
        }
        done(1);
    }
}

void question::on_pushButton_2_clicked()
{
    username_password form(this);
    if(form.exec())
    {
        char *ip = server_ip;
        char buffer[100];
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_port = htons(9999);


          // Connect to Server
        int err = socket_connect_(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
          if (err == -1) {
                printf("ERROR: connect\n");
            }
        sprintf(buffer, "s %s %s", username.toStdString().c_str(), password.toStdString().c_str());
        send(sockfd, buffer, strlen(buffer), 0);
        char reply[10];
        while(1)
        {
            int receive = recv(sockfd, reply, 10, 0);
            if(receive>0)
            {
                if(reply[0]=='a')
                {
                    QMessageBox msgBox(this);
                    msgBox.setText("User created\n You may log in");
                    msgBox.exec();
                    socket_close_(sockfd);
                    break;
                }
                if(reply[0]=='e')
                {
                    QMessageBox msgBox(this);
                    msgBox.setText("User exists");
                    msgBox.exec();
                    socket_close_(sockfd);
                    return;
                }
            }
            /*else
            {
                socket_close_(sockfd);
                done(-1);
            }*/
        }
    }
}
