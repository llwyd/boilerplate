#ifndef HEAP_H_
#define HEAP_H_

#include "assert_bp.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "state.h"

#define HEAP_LEN (16U)

typedef struct
{
    uint32_t key;
    event_t event;
}
heap_data_t;

typedef struct 
{
    heap_data_t * heap[HEAP_LEN];
    heap_data_t buffer[HEAP_LEN];
    uint32_t fill;
    uint32_t max;
}
heap_t;

extern void Heap_Init(heap_t * heap);
extern void Heap_Push(heap_t * heap, heap_data_t data);
extern uint32_t Heap_Pop(heap_t * heap);
extern heap_data_t Heap_PopFull(heap_t * heap);
extern uint32_t Heap_Peek(heap_t * heap);
extern bool Heap_IsEmpty(heap_t * heap);
extern bool Heap_IsFull(heap_t * heap);

#endif /* HEAP_H_ */

