//
// Created by lucas on 20/01/23.
//
#include <stdio.h>
#include "../src/cbitset.h"

int main() {
    /*// Just some development testing shit, proper tests will come along I swear
    cflag_ptr cflag = cflags_create(8);
    cflags_set_multiple(cflag, 3, 1, 2, 3);
    cflags_flip_multiple(cflag, 3, 1, 2, 3);
    //cflags_unset_multiple(cflag, 3, 0, 4, 5);
    bool is_set = cflags_any_set(cflag);
    if (is_set)
        printf("is set\n");
    else
        printf("isn't set\n");
    cflags_free(cflag);*/

    cbitset_ptr cbitset = cbitset_create(128, false);
    cbitset_set(cbitset, 0);
    cbitset_set(cbitset, 127);
    bool t = cbitset_is_set(cbitset, 127);
    cbitset_free(cbitset);
    if (t) {
        printf("set\n");
    }
    return 0;
}