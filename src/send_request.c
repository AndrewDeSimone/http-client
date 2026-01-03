#include <winsock2.h>
#include <stddef.h>

int send_request(SOCKET sock, char* request) {
    size_t total_sent = 0;
    size_t request_length = strlen(request);
    while (total_sent < request_length) {
        int sent = send(sock, request+total_sent, (int)(request_length - total_sent), 0);
        if (sent == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK) {
                continue;
            }
            return -1;
        }
        total_sent += sent;
    }

    return (int)total_sent;
}