#include "tests_bp.h"
#include <string.h>

extern void * TESTBP_memset(void * buffer, int ch, size_t len)
{
    return memset(buffer, ch, len);
}
