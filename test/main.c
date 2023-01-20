//
// Created by lucas on 20/01/23.
//
#include <stdio.h>
#include "../src/cflags.h"

int main() {
    // Just some development testing shit, proper tests will come along I swear
    struct cflag_s* cflag = cflags_create(64);
    cflags_flip(cflag, 6);
    bool is_set = cflags_is_set(cflag, 6);
    if (is_set)
        printf("is set\n");
    else
        printf("isn't set\n");
    cflags_free(cflag);
    return 0;
}git@github.com:IkeYeek/CFlags.git