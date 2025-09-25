#include "pq_base.h"
#include "assert_bp.h"
#include "util.h"

extern void PQ_Init(pq_t * const pq,
        pq_key_t * pool,
        uint8_t bytes)
{
    ASSERT(pq != NULL);
    ASSERT(pool != NULL);
    pq->fill = 0;
    pq->max = PQ_DEFAULT_LEN;

    uint8_t * pool8 = (uint8_t*)pool;
    for(uint32_t idx = 0u; idx < PQ_FULL_LEN; idx++)
    {
        pq->heap[idx] = (pq_key_t*)pool8;
        memset(pq->heap[idx], 0xFF, sizeof(pq_key_t));
        pool8 += bytes;
    }
}
