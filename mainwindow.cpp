#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "magic.h"
#include <string>
#include <QTimer>
#include <ctime>
#include <QCloseEvent>
#include <QThread>
void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this ->text = " ";
    char *ip = "127.0.0.1";
    int port = atoi("8888");
    strcpy(name, "MrPipiKado");
    str_trim_lf(name, strlen(name));
    if (strlen(name) > 32 || strlen(name) < 2){
        printf("Name must be less than 30 and more than 2 characters.\n");
        //return EXIT_FAILURE;
    }

    /* Socket settings */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);


      // Connect to Server
    int err = socket_connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
      if (err == -1) {
            printf("ERROR: connect\n");
        }
    send(sockfd, name, 32, 0);
    reciever = new RECIEVER(&sockfd, &server_addr);
    connect(reciever , SIGNAL(reciever(QString)),   this, SLOT(set_msg(QString)));
    reciever->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::set_msg(QString msg)
{
    ui->textEdit->setText(ui->textEdit->toPlainText()+msg);
}

void MainWindow::on_pushButton_clicked()
{
    char message[LENGTH] = {};
    char buffer[LENGTH + 32] = {};
    strcpy(message,ui->lineEdit->text().toStdString().c_str());
    sprintf(buffer, "%s: %s\n", name, message);
    ui->textEdit->setText(ui->textEdit->toPlainText()+"You: "+ui->lineEdit->text());
    ui->lineEdit->clear();
    send(sockfd, buffer, strlen(buffer), 0);
}
