#include <unistd.h>
#include "tcp-app.h"

int main(int argc, char *argv[])
{
    int opt;
    char mode;
    int port;
    char addr_str[IP_ADDR_STR_LEN_MAX];
    struct in_addr addr;

    memset(addr_str, '\0', IP_ADDR_STR_LEN_MAX);
    memset(&addr, 0, sizeof(struct in_addr));

    while ((opt = getopt(argc, argv, "m:p:a:")) != -1) {
        switch (opt) {
            case 'm':
                mode = optarg[0];
                logd("Mode: %s", mode == 's' ? "server" : mode == 'c' ? "client" : "?");
                break;
            case 'p':
                port = atoi(optarg);
                logd("Port: %d", port);
                break;
            case 'a':
                strncpy(addr_str, optarg, IP_ADDR_STR_LEN_MAX);
                logd("Address: %s", addr_str);
                break;
            default:
                loge("Invalid argument");
                exit(EXIT_FAILURE);
                break;
        }
    }

    if ((port < 0) || (port > 65535)) {
        loge("Invalid port %d", port);
        exit(EXIT_FAILURE);
    }

    switch (mode) {
        case 's':
            tcp_server((uint16_t)port);
            break;
        case 'c':
            if (inet_pton(AF_INET, addr_str, &addr) != 1) {
                loge("Invalid address");
                exit(EXIT_FAILURE);
            }
            tcp_client(addr, (uint16_t)port);
            break;
        default:
            loge("Invalid mode");
            exit(EXIT_FAILURE);
            break;
    }
}
