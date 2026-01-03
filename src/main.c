#include "url_parser.h"
#include "request_builder.h"
#include "create_socket.h"
#include "send_request.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    printf("Fetching: %s\n", argv[1]);

    struct url parsed_url = parse_url(argv[1]);

    if (parsed_url.valid == 0) {
        fprintf(stderr, "Error: invalid url");
        return 2;
    }

    char* request = build_request(parsed_url);

    if (request == NULL) {
        fprintf(stderr, "Error: insufficient memory");
        return 3; 
    }

    SOCKET sock = create_socket(parsed_url.host, parsed_url.port);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Error: failed to create socket\n");
        free(request);
        WSACleanup();
        return 4;
    }

    if (send_request(sock, request) == -1) {
        fprintf(stderr, "Error: failed to send request\n");
        free(request);
        closesocket(sock);
        WSACleanup();
        return 5;
    }

    free(request);

    //listen for response

    closesocket(sock);
    WSACleanup();

    return 0;
}