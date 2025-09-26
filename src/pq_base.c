#include "pq_base.h"
#include "assert_bp.h"
#include "util.h"

static void swap( pq_key_t ** a, pq_key_t ** b )
{
    ASSERT(a != NULL);
    ASSERT(b != NULL);

    pq_key_t * temp = *a;
    *a = *b;
    *b = temp;
}

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

extern pq_key_t * const PQ_Push(pq_t * pq, uint32_t key)
{
    ASSERT(pq != NULL);
    ASSERT(pq->fill < pq->max);
    ASSERT(key > 0u);

    const uint32_t fill = pq->fill;

    /* Add the value to the bottom of the heap */
    pq->heap[fill]->key = key;
    pq_key_t * ret_ptr = pq->heap[fill];
    uint32_t idx = fill;

    /* Swim through the heap to ensure heap order is correct */
    while( idx > 0U )
    {
        uint32_t parent = (idx - 1) >> 1U;
        if( pq->heap[idx]->key < pq->heap[parent]->key )
        {
            swap(&pq->heap[idx], &pq->heap[parent]);
        }
        idx = parent;
    }
    pq->fill++;

    return ret_ptr;
}

extern const pq_key_t * const PQ_Peek(pq_t * pq, uint32_t idx)
{
    ASSERT(pq != NULL);
    ASSERT(idx < pq->fill);
    ASSERT(pq->fill > 0U);
    
    return pq->heap[idx];
}

extern pq_key_t * const PQ_Pop(pq_t * pq)
{
    ASSERT(pq != NULL);
    ASSERT(pq->fill > 0U);


    /* 'Extract' top by placing at the end of the queue
     *  which is used as storage
     */
    
    swap(&pq->heap[0], &pq->heap[PQ_STORAGE_IDX]);
    pq_key_t * ret_ptr = pq->heap[PQ_STORAGE_IDX];

    /* Place bottom of heap at top */
    swap(&pq->heap[0], &pq->heap[pq->fill - 1U]);
    pq->heap[pq->fill - 1U]->key = UINT32_MAX;
    pq->fill--;

    /* Sink through the heap */
    uint32_t idx = 0U;
    uint32_t jdx = (idx << 1U) + 1U;

    while(jdx < pq->fill)
    {
        if(pq->heap[jdx]->key > pq->heap[jdx+1]->key)
        {
            jdx++;
        }

        if(pq->heap[idx]->key > pq->heap[jdx]->key)
        {
            swap(&pq->heap[idx], &pq->heap[jdx]);
            idx = jdx;
            jdx = (idx << 1U) + 1U;
        }
        else
        {
            break;
        }
    }

    return ret_ptr;
}

extern const pq_key_t * const PQ_DecreaseKey(pq_t * pq, uint32_t idx, uint32_t key)
{
    ASSERT(pq != NULL);
    ASSERT(idx < pq->fill);

    pq->heap[idx]->key = key;
    pq_key_t * ret_ptr = pq->heap[idx];
    
    uint32_t jdx = idx;
    /* Swim through the heap to ensure heap order is correct */
    while( jdx > 0U )
    {
        uint32_t parent = (jdx - 1) >> 1U;
        if( pq->heap[jdx]->key < pq->heap[parent]->key )
        {
            swap(&pq->heap[jdx], &pq->heap[parent]);
        }
        jdx = parent;
    }
    return ret_ptr;
}

extern bool PQ_IsFull(pq_t * pq)
{
    ASSERT(pq != NULL);
    return (pq->fill < pq->max);
}

extern bool PQ_IsEmpty(pq_t * pq)
{
    ASSERT(pq != NULL);
    return (pq->fill == 0U);
}
