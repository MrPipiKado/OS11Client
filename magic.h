#ifndef MAGIC_H
#define MAGIC_H
#include <sys/socket.h>
#include <unistd.h>
int (*socket_connect)(int, const struct sockaddr *, socklen_t) = connect;
int (*socket_close)(int) = close;
#endif // MAGIC_H
