#include "socket_utils.h"

struct sockaddr_in *create_ip4_addr(char *ip, int port)
{
  struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  if (!address) // malloc fail
    return NULL;
  address->sin_family = AF_INET;
  address->sin_port = htons(port); // convert int 16 bits

  if (!ip || strlen(ip) == 0)
    address->sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, ip, &address->sin_addr);
  return address;
}

int create_ip4_socket(void)
{
  return socket(AF_INET, SOCK_STREAM, 0);
}

accepted_client *recive_client(int server_socket_fd)
{
  struct sockaddr_in address = {0};
  size_t size_address = sizeof address;
  int client_fd = accept(server_socket_fd, (struct sockaddr *)&address, &size_address);

  accepted_client *result = (accepted_client *)malloc(sizeof(accepted_client));
  if (!result)
    return NULL;

  result->accept_successfuly = (client_fd > 0) ? 1 : 0;
  result->address = address;
  result->socket_fd = client_fd;
  if (result->accept_successfuly == 0)
    result->socket_error = client_fd;

  return result;
}

void client_thread(accepted_client *client)
{
  if (client->accept_successfuly != 0)
    return;
}