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
/**
 * Initializes the boolean byte array
 * @param size if auto_grow, the starting capacity eg. the amount of boolean values it can hold. if not, the maximum capacity
 * @param auto_grow should the byte array grow if we try to read/write in out-of-bound places.
 * @return an initialized pointer to the struct cbitset_s
 */
cbitset_ptr cbitset_create(unsigned int size, bool auto_grow);
/* === basic single value operations === */
/**
 * Sets a specific bit of the array to 1
 * eg. - setting the 5th bit
 *      initial_state:   00000001
 *      initial_state |= 1 << 5
 *  <=> initial_state |= 01000000
 *      initial_state  = 01000001
 * @param cbitset_ptr an initialized pointer to the struct cbitset_s
 * @param index index of the bit to set to 1
 */
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
