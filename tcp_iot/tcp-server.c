#include "tcp-app.h"

#define SERVER_BUFFER_LEN 1024

void tcp_server(uint16_t port)
{
    int sockfd;
    struct sockaddr_in clientAddr;

    int conn_sockfd;
    struct sockaddr_in newAddr;

    socklen_t addr_size;
    char buffer[SERVER_BUFFER_LEN];

    int ret;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        loge("Create Server Socket Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Server Socket Created Sucessfully.");
    memset(&clientAddr, '\0', sizeof(clientAddr));

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(port);
    clientAddr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    if (-1 == ret) {
        loge("Bind to Socket Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Bind to Port number %d.", port);

    ret = listen(sockfd, 5);
    if (-1 == ret) {
        loge("Listen to Socket Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Listening...");

    conn_sockfd = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
    if (-1 == conn_sockfd) {
        loge("Accept New Connection Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Accepted New Connection");

	addr_size = sizeof(newAddr);

    while (fgets(buffer, SERVER_BUFFER_LEN, stdin) != NULL) {
		//logd("Entered into while and waiting for data...");
        ret = send(conn_sockfd, buffer, strlen(buffer), 0);
        if (-1 == ret) {
            loge("Send Fail. (%s)", strerror(errno));
			break;
        }
        if (buffer[0] == TERMINATE_CHAR) {
            break;
        }
		fflush(stdin); //added to flush stdin.
    }
    logd("Closing the connection.");
}
