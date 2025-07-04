#ifndef FIFO_BASE_
#define FIFO_BASE_

#include "assert_bp.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FIFO_Enqueue(f, val) ((f)->in = (val), FIFO_EnQ((fifo_base_t *)(f)))
#define FIFO_Dequeue(f) ((FIFO_DeQ((fifo_base_t *)(f))), (f)->out)
#define FIFO_Peek(f) ((FIFO_Pk((fifo_base_t *)(f))), (f)->out)

#define ENQUEUE_BOILERPLATE(TYPE, BASE) \
    { \
        TYPE * fifo = ((TYPE *)(BASE)); \
        \
        fifo->queue[ fifo->base.write_index ] = fifo->in; \
        fifo->base.write_index++; \
        fifo->base.fill++; \
        fifo->base.write_index = ( fifo->base.write_index & ( fifo->base.max - 1U ) ); \
    }

#define DEQUEUE_BOILERPLATE(TYPE, BASE) \
    { \
        TYPE * fifo = ((TYPE *)(BASE)); \
        \
        fifo->out = fifo->queue[ fifo->base.read_index ]; \
        fifo->base.read_index++; \
        fifo->base.fill--; \
        fifo->base.read_index = ( fifo->base.read_index & ( fifo->base.max - 1U ) ); \
    }

#define PEEK_BOILERPLATE(TYPE, BASE) \
    { \
        TYPE * fifo = ((TYPE *)(BASE)); \
        \
        fifo->out = fifo->queue[ fifo->base.read_index ]; \
    }

#define FLUSH_BOILERPLATE(TYPE, BASE) \
    { \
        TYPE * fifo = ((TYPE *)(BASE)); \
        \
        fifo->base.read_index = fifo->base.write_index; \
        fifo->base.fill = 0U; \
    }

typedef struct fifo_vfunc_t fifo_vfunc_t;
typedef struct 
{
    fifo_vfunc_t const * vfunc;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t fill;
    uint32_t max;
}
fifo_base_t;

struct fifo_vfunc_t
{
    void (*enq)(fifo_base_t * const base);
    void (*deq)(fifo_base_t * const base);
    void (*peek)(fifo_base_t * const base);
    void (*flush)(fifo_base_t * const base);
};

inline static void FIFO_EnQ( fifo_base_t * const fifo )
{
    ASSERT( fifo != NULL );
    ASSERT( fifo->vfunc != NULL );
    ASSERT( fifo->fill < fifo->max );
    
    (fifo->vfunc->enq)(fifo);
}

inline static void FIFO_DeQ( fifo_base_t * const fifo )
{
    ASSERT( fifo != NULL );
    ASSERT( fifo->vfunc != NULL );
    ASSERT( fifo->fill > 0U );

    (fifo->vfunc->deq)(fifo);
}

inline static void FIFO_Flush( fifo_base_t * const fifo )
{
    ASSERT( fifo != NULL );
    ASSERT( fifo->vfunc != NULL );

    (fifo->vfunc->flush)(fifo);
}

inline static void FIFO_Pk( fifo_base_t * const fifo )
{
    ASSERT( fifo != NULL );
    ASSERT( fifo->vfunc != NULL );
    ASSERT( fifo->fill > 0U );

    (fifo->vfunc->peek)(fifo);
}

extern void FIFO_Init( fifo_base_t * const fifo, uint32_t size );
extern bool FIFO_IsFull( fifo_base_t const * const fifo );
extern bool FIFO_IsEmpty( fifo_base_t const * const fifo );

#endif /* FIFO_BASE_ */

