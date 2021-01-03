#ifndef RECIEVER_H
#define RECIEVER_H
#include <QThread>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class RECIEVER : public QThread
{
    Q_OBJECT

    public:
        explicit RECIEVER(int *sockfd, struct sockaddr_in *server_addr,QObject *parent = 0, bool b = false);
        void run();

        // if Stop = true, the thread will break
        // out of the loop, and will be disposed
        bool Stop;
        int *sockfd;
        struct sockaddr_in *server_addr;
    signals:
        // To communicate with Gui Thread
        // we need to emit a signal
        void reciever(QString);

    public slots:


    };

#endif // RECIEVER_H
