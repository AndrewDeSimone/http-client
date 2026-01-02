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

static void skip_scheme(const char* url, int* urlOffset) {
    if(strncmp(url, "http://", 7) == 0){
        *urlOffset += 7;
    }
}

static int parse_host(const char* url, struct url* result, int* urlOffset) {
    int hostOffset = 0;
    while (1) {
        char curr = url[*urlOffset];
        if (curr == '\0' || curr == ':' || curr == '/') {
            break;
        }
        if (hostOffset >= 255) {
            return 0;
        }

        result->host[hostOffset] = url[*urlOffset];

        hostOffset++;
        (*urlOffset)++;
    }
    result->host[hostOffset] = '\0';

    return 1;
}

static int parse_port(const char* url, struct url* result, int* urlOffset) {
    if (url[*urlOffset] != ':'){
        return 1;
    }
    (*urlOffset)++;

    result->port = 0;
    while (1) {
        char curr = url[*urlOffset];
        if (curr == '\0' || curr == '/') {
            break;
        }

        if (!isdigit(curr)) {
            return 0;
        }

        result->port *= 10;
        result-> port += curr - '0';

        (*urlOffset)++;
    }

    if (result->port > 65535) {
        return 0;
    } 

    return 1;
}

static int parse_path(const char* url, struct url* result, int* urlOffset) {
    if (url[*urlOffset] != '/'){
        return 1;
    }
    (*urlOffset)++;

    int pathOffset = 1;
    while (1) {
        char curr = url[*urlOffset];
        if (curr == '\0') {
            break;
        }
        if (pathOffset >= 1023) {
            return 0;
        }

        result->path[pathOffset] = url[*urlOffset];

        pathOffset++;
        (*urlOffset)++;
    }
    result->path[pathOffset] = '\0';

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

    int urlOffset = 0;

    skip_scheme(url, &urlOffset);
    if (
        !parse_host(url, &result, &urlOffset) ||
        !parse_port(url, &result, &urlOffset) ||
        !parse_path(url, &result, &urlOffset)
    ){
        return result;
    }

    result.valid = 1;
    return result;
}