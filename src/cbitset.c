//
// Created by lucas on 23/01/23.
//
#include <stdlib.h>
#include <stdio.h>
#include "cbitset.h"

static inline void flag_nullity_check(cbitset_ptr cbitsetP) {
    if (NULL == cbitsetP) {
        fprintf(stderr, "Cannot operate on an initialized flag\n");
        exit(1);
    }
}

/**
 * Initializes the boolean byte array
 * @param size if auto_grow, the starting capacity eg. the amount of boolean values it can hold. if not, the maximum capacity
 * @param auto_grow should the byte array grow if we try to read/write in out-of-bound places.
 * @return an initialized pointer to the struct cbitset_s
 */
cbitset_ptr cbitset_create(const unsigned int size, const bool auto_grow) {
    cbitset_ptr cbitset = malloc(sizeof(struct cbitset_s));
    cbitset->size = size;
    cbitset->auto_grow = auto_grow;
    cbitset->flag = (unsigned char*)calloc((size / 8) + (size % 8 != 0), sizeof(unsigned char*));

    return cbitset;
}

char *generate_mask(cbitset_ptr cbitsetP) {
    return calloc(cbitsetP->size, 1);
}


/**
 * Sets a specific bit of the array to 1
 * @param cbitset_ptr an initialized pointer to the struct cbitset_s
 * @param index index of the bit to set to 1
 */
void cbitset_set(cbitset_ptr cbitsetP, const unsigned int index) {
    flag_nullity_check(cbitsetP);
    unsigned int i = index / 8u;
    unsigned int j = index - (i * 8u);

    (cbitsetP->flag[i]) |= (unsigned char)1u << j;
}

void cbitset_flip(cbitset_ptr cbitsetP, const unsigned int index) {
    flag_nullity_check(cbitsetP);
    unsigned int i = index / 8u;
    unsigned int j = index - (i * 8u);

    (cbitsetP->flag[i])^= (unsigned char)1u << j;
}

void cbitset_unset(cbitset_ptr cbitsetP, const unsigned int index) {
    flag_nullity_check(cbitsetP);
    unsigned int i = index / 8u;
    unsigned int j = index - (i * 8u);

    (cbitsetP->flag[i]) &= ~(1u << j);
}

bool cbitset_is_set(cbitset_ptr cbitsetP, const unsigned int index) {
    flag_nullity_check(cbitsetP);
    unsigned int i = index / 8u;
    unsigned int j = index - (i * 8u);

    return ((cbitsetP->flag[i]) & (1u << j)) == (1u << j);
}

void cbitset_free(cbitset_ptr cbitsetP) {
    if (NULL == cbitsetP)
        return;


    free(cbitsetP->flag);
    free(cbitsetP);
}