#include "../include/slow_cycle.h"

extern DS_Data Global_Data;

void async_slow_clk_cycle_100ms(void) {
    unsigned long int act;
    static unsigned long int old;
    static bool skip = false;
    act = uz_SystemTime_GetUptimeInMs();

    if (!skip && (act % (100) < 50)) {
        async_slow_clk_cycle_100ms_wrapper();
        skip = true;
        Global_Data.av.slow_cycle_period_ms = (float)(act - old);
        old = act;
    }
    if (((old + 99) < act) || (act < old)) {
        skip = false; 
    }
}

void async_slow_clk_cycle_100ms_wrapper(void) {
    //EXECUTE HERE
    Global_Data.av.EnDat_value_calc_time = uz_EnDat_time_elapsed_ns_to_s_converter(uz_EnDat_read_time_elapsed(Global_Data.objects.EnDat_master_pointer, uz_EnDat_elapsed_t0_t1));
    uz_EnDat_fetch_statusword_and_errorbit_from_EnDat_object_and_write_to_object(Global_Data.objects.EnDat_master_pointer);
}
