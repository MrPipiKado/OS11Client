#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "reciever.h"
#define LENGTH 2048
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void set_msg(QString msg);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int sockfd;
    RECIEVER *reciever ;
    struct sockaddr_in server_addr;
    char name[32];
    QString text;
};
#endif // MAINWINDOW_H
