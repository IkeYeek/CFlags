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

typedef struct cflag_s* cflag_ptr;

cflag_ptr cflags_create(int size);

void cflags_set(cflag_ptr flag, int position);
void cflags_set_multiple(cflag_ptr flag, int nb_to_set, ...);

void cflags_unset(cflag_ptr flag, int position);
void cflags_unset_multiple(cflag_ptr flag, int nb_to_remove, ...);

void cflags_flip(cflag_ptr flag, int position);
void cflags_flip_multiple(cflag_ptr flag, int nb_to_flip, ...);

bool cflags_is_set(cflag_ptr flag, int position);
bool cflags_all_set(cflag_ptr flag);
bool cflags_are_set(cflag_ptr flag, int nb_to_poll, ...);
bool cflags_any_set(cflag_ptr flag);
void cflags_free(cflag_ptr flag);

#endif //CFLAGS_CFLAGS_H
