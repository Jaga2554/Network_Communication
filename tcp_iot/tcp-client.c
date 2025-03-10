#include "tcp-app.h"
#include "response.h"

#define CLIENT_BUFFER_LEN 1024

void tcp_client(struct in_addr addr, uint16_t port)
{
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[CLIENT_BUFFER_LEN];
	char response[CLIENT_BUFFER_LEN];
    int ret;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        loge("Create Client Socket Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Client Socket Created Sucessfully.");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr = addr;

    ret = connect(sockfd, (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));
    if (-1 == ret) {
        loge("Connect to Server Fail. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
    }
    logd("Connected to Server.");

    while (1) {
        ret = recv(sockfd, buffer, CLIENT_BUFFER_LEN, 0);
        if (-1 == ret) {
            loge("Receive Fail. (%s)", strerror(errno));
            exit(EXIT_FAILURE);
                break;
            }
			if (ret == 0) {
				logd("Server closed connection..");
				break;
			}
            if (buffer[0] == TERMINATE_CHAR) {
				break;
        }
		printf("Received: %s", buffer); //print received data.
		
		// Process command and generate response
		if(strncmp(buffer, "/imsi", 5) == 0) {
			generate_response(buffer, response, CLIENT_BUFFER_LEN);
			send(sockfd, response, strlen(response), 0);
		} else if (strncmp(buffer, "/imei", 5) == 0) {
			generate_response(buffer, response, CLIENT_BUFFER_LEN);
			send(sockfd, response, strlen(response), 0);
		}
		//logd("Respone sent to server: %s", response);
	}
    logd("Closing the connection.");
}
