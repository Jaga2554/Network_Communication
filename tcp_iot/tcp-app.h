#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cjson/cJSON.h>

#include "debug.h"

#define IP_ADDR_STR_LEN_MAX 16 /* "xxx.xxx.xxx.xxx" */
#define TERMINATE_CHAR '`'

void tcp_client(struct in_addr addr, uint16_t port);
void tcp_server(uint16_t port);
