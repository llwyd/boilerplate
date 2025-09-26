#ifndef PQ_BASE_H
#define PQ_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef PQ_DEFAULT_LEN
#define PQ_DEFAULT_LEN (16u)
/* extra 1 is necessary for storage when popping as storage */
#define PQ_FULL_LEN (PQ_DEFAULT_LEN + 1u)
#define PQ_STORAGE_IDX (PQ_FULL_LEN - 1u)
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

extern const pq_key_t * const PQ_Peek(pq_t * pq, uint32_t idx);
extern pq_key_t * const PQ_Push(pq_t * pq, uint32_t key);
extern pq_key_t * const PQ_Pop(pq_t * pq);
extern bool PQ_IsEmpty(pq_t * pq);
extern bool PQ_IsFull(pq_t * pq);

#endif /* PQ_BASE_H */
