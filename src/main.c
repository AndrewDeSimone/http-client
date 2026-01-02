#include "url_parser.h"
#include <stdio.h>
#include <string.h>

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

    printf("Host name: %s\n", parsed_url.host);
    printf("Port number: %d\n", parsed_url.port);
    printf("Path: %s\n", parsed_url.path);

    return 0;
}