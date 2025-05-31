#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HEAP_LEN (8U)

typedef struct
{
    uint32_t key;
}
heap_data_t;

typedef struct 
{
    heap_data_t heap[HEAP_LEN];
    uint32_t fill;
    uint32_t max;
}
heap_t;

extern void Heap_Init(heap_t * heap);
extern void Heap_Push(heap_t * heap, heap_data_t data);
extern uint32_t Heap_Pop(heap_t * heap);
extern uint32_t Heap_Peek(heap_t * heap);
extern bool Heap_IsEmpty(heap_t * heap);
extern bool Heap_IsFull(heap_t * heap);

