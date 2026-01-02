#include "url_parser.h"
#include <string.h>
#include <ctype.h>

static struct url init_url_defaults(){
    struct url result;
    result.host[0] = '\0';
    result.port = 80;
    strcpy(result.path, "/");
    result.valid = 0;
    return result;
}

static void skip_scheme(const char* url, int* url_offset) {
    if(strncmp(url, "http://", 7) == 0){
        *url_offset += 7;
    }
}

static int parse_host(const char* url, struct url* result, int* url_offset) {
    int host_offset = 0;
    while (1) {
        char curr = url[*url_offset];
        if (curr == '\0' || curr == ':' || curr == '/') {
            break;
        }
        if (host_offset >= 255) {
            return 0;
        }

        result->host[host_offset] = url[*url_offset];

        host_offset++;
        (*url_offset)++;
    }
    result->host[host_offset] = '\0';

    return 1;
}

static int parse_port(const char* url, struct url* result, int* url_offset) {
    if (url[*url_offset] != ':'){
        return 1;
    }
    (*url_offset)++;

    result->port = 0;
    while (1) {
        char curr = url[*url_offset];
        if (curr == '\0' || curr == '/') {
            break;
        }

        if (!isdigit(curr)) {
            return 0;
        }

        result->port *= 10;
        result-> port += curr - '0';

        (*url_offset)++;
    }

    if (result->port > 65535) {
        return 0;
    } 

    return 1;
}

static int parse_path(const char* url, struct url* result, int* url_offset) {
    if (url[*url_offset] != '/'){
        return 1;
    }
    (*url_offset)++;

    int path_offset = 1;
    while (1) {
        char curr = url[*url_offset];
        if (curr == '\0') {
            break;
        }
        if (path_offset >= 1023) {
            return 0;
        }

        result->path[path_offset] = url[*url_offset];

        path_offset++;
        (*url_offset)++;
    }
    result->path[path_offset] = '\0';

    return 1;
}

/*
* [http://]host[:port][/path]
*/
struct url parse_url(const char* url){

    struct url result = init_url_defaults();

    if (url == NULL){
        return result;
    }

    int url_offset = 0;

    skip_scheme(url, &url_offset);
    if (
        !parse_host(url, &result, &url_offset) ||
        !parse_port(url, &result, &url_offset) ||
        !parse_path(url, &result, &url_offset)
    ){
        return result;
    }

    result.valid = 1;
    return result;
}