#include <iostream>
#include <sys/socket.h>
#include <cerrno>
#include <netdb.h>
#include <cstring>

#define PROXY_PORT 52784
#define CONNECTIONS_BACKLOG 10

int main() {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    char portString[16];
    snprintf(portString, 16, "%d", PROXY_PORT);
    getaddrinfo(NULL, portString, &hints, &res);

    int proxySocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (proxySocket < 0){
        perror("Failed to create client to proxy socket");
        exit(EIO);
    }

    if (bind(proxySocket, res->ai_addr, res->ai_addrlen) < 0){
        perror("Failed to bind client to proxy socket");
        exit(EIO);
    }

    if (listen(proxySocket, CONNECTIONS_BACKLOG) < 0){
        perror("Failed listen() client to proxy socket");
        exit(EIO);
    }

    while (true){
        int clientSocket = accept(proxySocket, NULL, NULL);
        if (clientSocket == -1){
            perror("accept()");
            return -1;
        }

        std::cout << "Server: new connection!\n";

        char buf[4096];
        while (recv(clientSocket, buf, 4096, 0) != 0){
            std::cout << buf;
        }
    }



    return 0;
}

