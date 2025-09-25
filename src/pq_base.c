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

#if 0
extern pq_key_t * const PQ_Peek(pq_t * pq, uint32_t key)
    ASSERT(heap != NULL);
    ASSERT(!Heap_IsEmpty(heap));
    ASSERT(heap->fill > 0U);
    
    return heap->heap[0U]->key;
}
extern pq_key_t * const PQ_Pop(pq_t * pq, uint32_t key)
{
    ASSERT(heap != NULL);
    ASSERT(!Heap_IsEmpty(heap));
    ASSERT(heap->fill > 0U);

    uint32_t top = heap->heap[0]->key;

    /* Place bottom of heap at top */
    swap(&heap->heap[0], &heap->heap[heap->fill - 1U]);
    heap->heap[heap->fill - 1U]->key = UINT32_MAX;
    heap->fill--;

    /* Sink through the heap */
    uint32_t idx = 0U;
    uint32_t jdx = (idx << 1U) + 1U;

    while(jdx < heap->fill)
    {
        if(heap->heap[jdx]->key > heap->heap[jdx+1]->key)
        {
            jdx++;
        }

        if(heap->heap[idx]->key > heap->heap[jdx]->key)
        {
            swap(&heap->heap[idx], &heap->heap[jdx]);
            idx = jdx;
            jdx = (idx << 1U) + 1U;
        }
        else
        {
            break;
        }
    }

    return top;
}
#endif
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
