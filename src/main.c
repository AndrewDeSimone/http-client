#include <stdio.h>

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    printf("Fetching: %s\n", argv[1]);

    return 0;
}