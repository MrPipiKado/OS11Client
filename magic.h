#ifndef MAGIC_H
#define MAGIC_H
#include <sys/socket.h>

int (*socket_connect)(int, const struct sockaddr *, socklen_t) = connect;
#endif // MAGIC_H
