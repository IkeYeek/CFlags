//
// Created by lucas on 23/01/23.
//

#ifndef CFLAGS_cbitset_H
#define CFLAGS_cbitset_H

#include <stdbool.h>

struct cbitset_s {
    unsigned int size;
    bool auto_grow;
    unsigned char *flag;
};

typedef struct cbitset_s* cbitset_ptr;
cbitset_ptr cbitset_create(unsigned int size, bool auto_grow);
void cbitset_set(cbitset_ptr cbitsetP, unsigned int index);
void cbitset_flip(cbitset_ptr cbitsetP, unsigned int index);
void cbitset_unset(cbitset_ptr cbitsetP, unsigned int index);
bool cbitset_is_set(cbitset_ptr cbitsetP, unsigned int index);

char *generate_mask(cbitset_ptr cbitsetP);

/**
 * Frees a boolean byte array.
 * @param bbpa_ptr
 */
void cbitset_free(cbitset_ptr cbitsetP);

#endif //CFLAGS_cbitset_H
