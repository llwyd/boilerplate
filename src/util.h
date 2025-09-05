#ifndef __UTIL_H_
#define __UTIL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

__attribute__((weak))
extern void * memset(void * dest, int ch, size_t len)
{
    uint8_t * d = (uint8_t *)dest;

    while(len > 0U)
    {
        *d = (uint8_t)ch;
        d++;
        len--;
    }

    return dest;
}

#endif /* __UTIL_H_ */
