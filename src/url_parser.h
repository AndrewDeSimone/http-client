#ifndef URL_PARSER_H
#define URL_PARSER_H

struct url {
    char host[256];
    int port;
    char path[1024];
    int valid;
};

struct url parse_url(const char* url);

#endif