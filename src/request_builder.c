#include "url_parser.h"
#include "request_builder.h"
#include "utils/string_builder.h"
#include <stdlib.h>
#include <stdio.h>

/*
* GET [path] HTTP/1.1\r\n
* Host: [host][:port]\r\n
* \r\n
*/
char* build_request(struct url url) {
    struct sb builder;
    if (!sb_init(&builder, 128)) return NULL;

    sb_append(&builder, "GET ");
    sb_append(&builder, url.path);
    sb_append(&builder,  " HTTP/1.1\r\n");
    sb_append(&builder, "Host: ");
    sb_append(&builder, url.host);
    sb_append(&builder, ":");
    char port_str[16];
    snprintf(port_str, sizeof(port_str), "%d", url.port);
    sb_append(&builder, port_str);
    sb_append(&builder, "\r\n\r\n");

    return builder.buf;
}