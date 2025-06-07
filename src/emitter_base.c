#include "emitter_base.h"

static void Destroy(emitter_base_t * const base);
static void Create(emitter_base_t * const base, event_t event, uint32_t period);
static bool Emit(emitter_base_t * const base, event_t event);

extern void Emitter_Init(emitter_base_t * const base, fifo_base_t * fifo)
{
    ASSERT(base != NULL);
    ASSERT(base->fifo != NULL);

    static const emitter_vfunc_t vfunc =
    {
        .emit = Emit,
        .create = Create,
        .destroy = Destroy,
    };
    base->vfunc = &vfunc;
    base->fifo = fifo;
}



static bool Emit(emitter_base_t * const base, event_t event)
{
    (void)base;
    (void)event;
    ASSERT(false);
    return false;
}

static void Destroy(emitter_base_t * const base)
{
    (void)base;
    ASSERT(false);
}

static void Create(emitter_base_t * const base, event_t event, uint32_t period)
{
    (void)base;
    (void)event;
    (void)period;
    ASSERT(false);
}

