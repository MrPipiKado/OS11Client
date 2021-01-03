#include "reciever.h"
RECIEVER::RECIEVER(int *sockfd, struct sockaddr_in *server_addr,QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
    this->sockfd = sockfd;
    this->server_addr = server_addr;
}

void RECIEVER::run()
{
    char message[2048] = {};
      while (1) {
            int receive = recv(*sockfd, message, 2048, 0);
        if (receive > 0) {
          printf("%s", message);
          emit reciever(QString::fromStdString(std::string(message)));
        } else if (receive == 0) {
                break;
        } else {
                // -1
            }
            memset(message, 0, sizeof(message));
            this->msleep(1);
      }
}
