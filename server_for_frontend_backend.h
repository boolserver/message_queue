#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "msg_queue.h"

//#define SERVER_IP_ADDR "127.0.0.1"
#define PORT 5000
#define EMPTY_STR "00000000000000000000000000000000"

int client(const char* uuid_str);

