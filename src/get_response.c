#include "utils/string_builder.h"
#include <winsock2.h>

char* get_response(SOCKET sock) {
    
    struct sb builder;
    
    if(!sb_init(&builder, 120)) return NULL;
    
    while (1) {
        char buf[120];
        int size = recv(sock, buf, 120, 0);
        if (size == SOCKET_ERROR) {
            free(builder.buf);
            return NULL;
        }

        if (size == 0) {
            return builder.buf;
        }

        if (!sb_append_len(&builder, buf, size)){
            free(builder.buf);
            return NULL;
        } 
    }
}