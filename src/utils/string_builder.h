#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stddef.h>

struct sb {
    char *buf;
    size_t len;
    size_t cap;
};

int sb_init(struct sb* sb, size_t initial_cap);

int sb_append(struct sb* sb, const char* str);

int sb_append_len(struct sb* sb, const char* str, size_t len);

#endif