#ifndef CFLAGS_CFLAGS_H
#define CFLAGS_CFLAGS_H

#include <stdbool.h>

#define MAX_SYSTEM_SIZE sizeof(unsigned long long)

enum cflag_type {
    CHAR,
    SHORT,
    INT,
    LONG,
    LONGLONG,
};

struct cflag_s {
    int size;
    enum cflag_type type;
    void *flag;
};

struct cflag_s* cflags_create(int size);

void cflags_set(struct cflag_s* flag, int position);
void cflags_set_multiple(struct cflag_s* flag, int nb_to_set, ...);

void cflags_unset(struct cflag_s* flag, int position);
void cflags_unset_multiple(struct cflag_s* flag, int nb_to_remove, ...);

void cflags_flip(struct cflag_s* flag, int position);
void cflags_flip_multiple(struct cflag_s flag, int nb_to_flip, ...);

bool cflags_is_set(struct cflag_s* flag, int position);
bool cflags_all_set(struct cflag_s* flag);
bool cflags_are_set(struct cflag_s* flag, int nb_to_poll, ...);

void cflags_free(struct cflag_s* flag);

#endif //CFLAGS_CFLAGS_H
