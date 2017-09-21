#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdint.h>
#include <sys/select.h>

int make_socket(uint16_t port);

void listener(int socket, void (*handler)(int));

void loop(fd_set *read_fdset, void (*handler)(int));
#endif