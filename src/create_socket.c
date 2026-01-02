#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

SOCKET create_socket(const char* host, int port) {
    
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return INVALID_SOCKET;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (strcmp(host, "localhost") == 0) {
        // Resolve localhost to 127.0.0.1
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    } else {
        server.sin_addr.s_addr = inet_addr(host);
        if (server.sin_addr.s_addr == INADDR_NONE) {
            printf("Invalid IP address: %s\n", host);
            closesocket(sock);
            WSACleanup();
            return INVALID_SOCKET;
        }
    }

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connect failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return INVALID_SOCKET;
    }

    return sock;
}
