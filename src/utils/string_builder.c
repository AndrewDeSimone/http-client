#include "string_builder.h"
#include <stdlib.h>
#include <string.h>

int sb_init(struct sb* sb, size_t initial_cap) {
    if (initial_cap == 0) initial_cap = 16;
    sb->buf = malloc(initial_cap);
    if (sb->buf == NULL) return 0;

    sb->len = 0;
    sb -> cap = initial_cap;
    sb->buf[0] = '\0';

    return 1;
}

int sb_append(struct sb* sb, const char* str) {

    size_t added_length = strlen(str);
    size_t remaining_length = sb->cap - sb->len;
    while (added_length + 1 > remaining_length) {
        char *tmp = realloc(sb->buf, sb->cap * 2);
        if (!tmp) return 0;
        sb->buf = tmp;
        sb->cap *= 2;

        remaining_length = sb->cap - sb->len;
    }

    memcpy(sb->buf + sb->len, str, added_length);
    sb->len += added_length;
    sb->buf[sb->len] = '\0';

    return 1;
}

int sb_append_len(struct sb* sb, const char* str, size_t len) {
    size_t remaining_length = sb->cap - sb->len;

    while (len + 1 > remaining_length) {
        char* tmp = realloc(sb->buf, sb->cap * 2);
        if (!tmp) return 0;
        sb->buf = tmp;
        sb->cap *= 2;
        remaining_length = sb->cap - sb->len;
    }

    memcpy(sb->buf + sb->len, str, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
    return 1;
}