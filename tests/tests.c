#include "state_tests.h"
#include "fifo_tests.h"
#include "heap_tests.h"
#include "emitter_tests.h"
#include "event_observer_tests.h"
#include "scenario_tests.h"
#include "util_tests.h"
#include "unity.h"

int main( void )
{
    UNITY_BEGIN();

    FIFOTestSuite();
    STATETestSuite();
    HeapTestSuite();
    EMITTERTestSuite();
    EVENTOBSERVERTestSuite();
    SCENARIOTestSuite();
    UtilTestSuite();
    return UNITY_END();
}
