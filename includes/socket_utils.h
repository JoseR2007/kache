#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct accepted_client
{
  int socket_fd;
  struct sockaddr_in address;
  int socket_error; // 0 -> no errors
  int accept_successfuly;
} accepted_client;

struct sockaddr_in *create_ip4_addr(char *, int);
int create_ip4_socket(void);
accepted_client *recive_client(int);

#endif