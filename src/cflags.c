#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cflags.h"

static inline void check_flag(struct cflag_s *flag) {
    if (flag == NULL) {
        fprintf(stderr, "Cannot operate on unitialized flag !");
        exit(1);
    }
}

static inline void check_position(struct cflag_s *flag, int position) {
    if (position < 0) {
        fprintf(stderr, "Position must be positive, %d given !\n", position);
        exit(1);
    }
    if (position >= flag->size) {
        fprintf(stderr, "Trying to operate on a overflowing position (%d) !\n", position);
        exit(1);
    }
}

static inline void check_flag_and_position(struct cflag_s *flag, int position) {
    check_flag(flag);
    check_position(flag, position);
}

struct cflag_s* cflags_create(int size) {
    if (size <= 0) {
        fprintf(stderr, "Size must be positive and non-null, %d given !\n", size);
        exit(1);
    }
    if (size > MAX_SYSTEM_SIZE * 8) {
        fprintf(stderr, "Size of %d bits is exceeding the maximum size of a single word on this system (%lu "
                        "bytes / %lu bits)\n",
                size, MAX_SYSTEM_SIZE, MAX_SYSTEM_SIZE * 8);
        exit(1);
    }
    struct cflag_s* flag = malloc(sizeof(struct cflag_s));

    flag->size = size;

    if (size <= sizeof(unsigned char) * 8) {
        flag->flag = calloc(1, sizeof(unsigned char));
        flag->type = CHAR;
    } else if (size <= sizeof(unsigned short) * 8) {
        flag->flag = calloc(1, sizeof(unsigned short));
        flag->type = SHORT;
    } else if(size <= sizeof(unsigned int) * 8) {
        flag->flag = calloc(1, sizeof(unsigned int));
        flag->type = INT;
    } else if(size <= sizeof(unsigned long) * 8) {
        flag->flag = calloc(1, sizeof(unsigned long));
        flag->type = LONG;
    } else {
        flag->flag = calloc(1, sizeof(unsigned long long));
        flag->type = LONGLONG;
    }

    return flag;
}

void cflags_set(struct cflag_s* flag, int position) {
    check_flag_and_position(flag, position);

    switch (flag->type) {
        case CHAR:
            *(unsigned char*)flag->flag |= 1 << position;
            break;
        case SHORT:
            *(unsigned short*)flag->flag |= 1 << position;
            break;
        case INT:
            *(unsigned int*)flag->flag |= 1 << position;
            break;
        case LONG:
            *(unsigned long*)flag->flag |= 1 << position;
            break;
        case LONGLONG:
            *(unsigned long long*)flag->flag |= 1 << position;
            break;
        default:
            fprintf(stderr, "Unknown flag data structure type");
            exit(1);
    }
}

void cflags_unset(struct cflag_s* flag, int position) {
    check_flag_and_position(flag, position);
    switch (flag->type) {
        case CHAR:
            *(unsigned char*)flag->flag &= ~(1 << position);
            break;
        case SHORT:
            *(unsigned short*)flag->flag &= ~(1 << position);
            break;
        case INT:
            *(unsigned int*)flag->flag &= ~(1 << position);
            break;
        case LONG:
            *(unsigned long*)flag->flag &= ~(1 << position);
            break;
        case LONGLONG:
            *(unsigned long long*)flag->flag &= ~(1 << position);
            break;
        default:
            fprintf(stderr, "Unknown flag data structure type");
            exit(1);
    }
}

void cflags_flip(struct cflag_s* flag, int position) {
    check_flag_and_position(flag, position);
    switch (flag->type) {
        case CHAR:
            *(unsigned char*)flag->flag ^= 1 << position;
            break;
        case SHORT:
            *(unsigned short*)flag->flag ^= 1 << position;
            break;
        case INT:
            *(unsigned int*)flag->flag ^= 1 << position;
            break;
        case LONG:
            *(unsigned long*)flag->flag ^= 1 << position;
            break;
        case LONGLONG:
            *(unsigned long long*)flag->flag ^= 1 << position;
            break;
        default:
            fprintf(stderr, "Unknown flag data structure type");
            exit(1);
    }
}

bool cflags_is_set(struct cflag_s* flag, int position) {
    check_flag_and_position(flag, position);

    switch (flag->type) {
        case CHAR:
            return (*(unsigned char*)flag->flag & 1 << position) != 0;
        case SHORT:
            return (*(unsigned short*)flag->flag & 1 << position) != 0;
        case INT:
            return (*(unsigned int*)flag->flag & 1 << position) != 0;
        case LONG:
            return (*(unsigned long*)flag->flag & 1 << position) != 0;
        case LONGLONG:
            return (*(unsigned long long*)flag->flag & 1 << position) != 0;
        default:
            fprintf(stderr, "Unknown flag data structure type");
            exit(1);
    }
}

void cflags_set_multiple(struct cflag_s* flag, int nb_to_set, ...) {
    va_list to_set_flags;
    va_start(to_set_flags, nb_to_set);

    union {
        unsigned char c;
        unsigned short s;
        unsigned int i;
        unsigned long l;
        unsigned long ll;
    } bitmask;

    for (int i = 0; i < nb_to_set; i += 1) {
        switch (flag->type) {
            case CHAR:
                bitmask.c |= 1 << va_arg(to_set_flags, int);
                break;
            case SHORT:
                bitmask.s |= 1 << va_arg(to_set_flags, int);
                break;
            case INT:
                bitmask.i |= 1 << va_arg(to_set_flags, int);
                break;
            case LONG:
                bitmask.l |= 1 << va_arg(to_set_flags, int);
                break;
            case LONGLONG:
                bitmask.ll |= 1 << va_arg(to_set_flags, int);
                break;
            default:
                fprintf(stderr, "Unknown flag data structure type");
                exit(1);
        }
    }

    switch (flag->type) {
        case CHAR:
            *(unsigned char *) flag->flag |= bitmask.c;
            break;
        case SHORT:
            *(unsigned short *) flag->flag |= bitmask.s;
            break;
        case INT:
            *(unsigned int *) flag->flag |= bitmask.i;
            break;
        case LONG:
            *(unsigned long *) flag->flag |= bitmask.l;
            break;
        case LONGLONG:
            *(unsigned long long *) flag->flag |= bitmask.ll;
            break;
    }
    va_end(to_set_flags);
}

void cflags_free(struct cflag_s* flag) {
    if (flag == NULL)
        return;
    free(flag->flag);
    free(flag);
}