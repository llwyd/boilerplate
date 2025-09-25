#ifndef PQ_BASE_H
#define PQ_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef PQ_DEFAULT_LEN
#define PQ_DEFAULT_LEN (16u)
/* extra 1 is necessary for storage when popping as storage */
#define PQ_FULL_LEN (PQ_DEFAULT_LEN + 1u)
#endif

typedef struct
{
    uint32_t key;
}
pq_key_t;

typedef struct
{
    pq_key_t * heap[PQ_FULL_LEN];
    uint32_t fill;
    uint32_t max;
}
pq_t;

extern void PQ_Init(pq_t * const pq,
        pq_key_t * pool,
        uint8_t bytes);

#endif /* PQ_BASE_H */
