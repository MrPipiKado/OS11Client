#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "magic.h"
#include <string>
#include <QTimer>
#include <ctime>
#include <QCloseEvent>
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
    std::srand(time(nullptr));
    QTimer *timer = new QTimer(this);
    //pthread_t recv_msg_thread;
      /*if(pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0){
            printf("ERROR: pthread\n");
            //return EXIT_FAILURE;
        }*/
    connect(timer, &QTimer::timeout, this, &MainWindow::recv_msg_handler);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recv_msg_handler()
{
    char message[LENGTH] = {};
    int receive = recv(sockfd, message, LENGTH, 0);
    if (receive > 0) {
       //ui->textEdit->setText(ui->textEdit->toPlainText()+QString::fromStdString(std::string(message)));
    } else if (receive == 0) {
    } else {
    // -1
    }
    memset(message, 0, sizeof(message));
}

void MainWindow::on_pushButton_clicked()
{

}
