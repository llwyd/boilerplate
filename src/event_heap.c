#include "event_heap.h"

static void swap( heap_data_t ** a, heap_data_t ** b )
{
    ASSERT(a != NULL);
    ASSERT(b != NULL);

    
    heap_data_t * temp = *a;
    *a = *b;
    *b = temp;
}

extern void Heap_Init(heap_t * heap)
{
    heap->fill = 0;
    heap->max = HEAP_LEN;
    
    uint8_t * heap8 = (uint8_t *)&heap->buffer;
    uint32_t size = sizeof(heap_data_t) * HEAP_LEN;
    for(uint32_t idx = 0; idx < size; idx++)
    {
        *(heap8++) = 0xFF; 
    }

    for(uint32_t idx = 0; idx < HEAP_LEN; idx++)
    {
        heap->heap[idx] = &heap->buffer[idx];
    }
}

extern bool Heap_IsFull(heap_t * heap)
{
    ASSERT(heap != NULL);
    return (heap->fill < heap->max);
}

extern bool Heap_IsEmpty(heap_t * heap)
{
    ASSERT(heap != NULL);
    return (heap->fill == 0U);
}

extern void Heap_Push(heap_t * heap, heap_data_t data)
{
    (void)heap;
    (void)data;
    
    ASSERT(heap != NULL);
    ASSERT(heap->fill < heap->max);

    /* Add the value to the bottom of the heap */
    *heap->heap[heap->fill] = data;

    uint32_t idx = heap->fill;

    /* Swim through the heap to ensure heap order is correct */
    while( idx > 0U )
    {
        uint32_t parent = (idx - 1) >> 1U;
        if( heap->heap[idx]->key < heap->heap[parent]->key )
        {
            swap(&heap->heap[idx], &heap->heap[parent]);
        }
        idx = parent;
    }
    heap->fill++; 
}

extern uint32_t Heap_Peek(heap_t * heap)
{
    ASSERT(heap != NULL);
    ASSERT(!Heap_IsEmpty(heap));
    ASSERT(heap->fill > 0U);
    
    return heap->heap[0U]->key;
}

extern uint32_t Heap_Pop(heap_t * heap)
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

extern heap_data_t Heap_PopFull(heap_t * heap)
{
    ASSERT(heap != NULL);
    ASSERT(!Heap_IsEmpty(heap));
    ASSERT(heap->fill > 0U);

    heap_data_t top = *heap->heap[0];

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

