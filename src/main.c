#include "url_parser.h"
#include "request_builder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    printf(request);

    free(request);

    return 0;
}