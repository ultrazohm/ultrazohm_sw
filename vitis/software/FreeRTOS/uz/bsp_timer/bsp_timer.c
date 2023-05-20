/*
 * Copyright (c) 2022 Jens Wenzl
 * Author: Jens Wenzl jens_wenzl@t-online.de
 * Based on Xilinx TTC irq example
 *
 * Abstraction layer for timer
 */

#include "bsp_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"
#include "xstatus.h"
#include "xil_exception.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xil_printf.h"


/*-------------------------------------------------------------------
 * Configuration
 *-----------------------------------------------------------------*/
#define NUM_TTC_PS_DEVICES              12U
#define TTC_TICK_DEVICE_ID              XPAR_PSU_TTC_9_DEVICE_ID
#define TTC_TICK_INTR_ID                XPAR_XTTCPS_9_INTR
#define TTC_TIMESTAMP_DEVICE_ID         XPAR_PSU_TTC_10_DEVICE_ID
#define TTC_TIMESTAMP_CLK_IN            XPAR_PSU_TTC_9_TTC_CLK_FREQ_HZ

/*-------------------------------------------------------------------
 * Type definitions
 *-----------------------------------------------------------------*/
typedef struct {
    u32 OutputHz;
    XInterval Interval;
    u8 Prescaler;
    u16 Options;
} TmrCntrSetup;

/*-------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------*/
static XTtcPs TtcPsInst[NUM_TTC_PS_DEVICES];    /* Number of available timer counters */

static TmrCntrSetup SettingsTable[NUM_TTC_PS_DEVICES] = {
    [TTC_TICK_DEVICE_ID]{
        .OutputHz = 10000,
        .Interval = 0,
        .Prescaler = 0,
        .Options = (XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_WAVE_DISABLE)
    },
    [TTC_TIMESTAMP_DEVICE_ID]{
        // Not necessary for setup! Will be used for time calculations at runtime.
        .OutputHz = (TTC_TIMESTAMP_CLK_IN / (2 << 5)),
        .Interval = 0xFFFF, // Must be any of uint8_max, uint16_max, uint32_max
        .Prescaler = 5, // div_factor = 2 ^ (prescaler + 1) = (2 << prescaler)
        .Options = (XTTCPS_OPTION_WAVE_DISABLE)
    },
};

// IRQ controller. Already set up by uz isr setup
extern XScuGic INTCipc;
static XScuGic* gic_inst_p = &INTCipc;

/*-------------------------------------------------------------------
 * Local functions
 *-----------------------------------------------------------------*/
static void TickHandler(void *CallBackRef, u32 StatusEvent)
{
    if (0 != (XTTCPS_IXR_INTERVAL_MASK & StatusEvent)) {
        timer_irq_callback__();
    }
}

static int bsp_timer_init_ip(int DeviceID)
{
    int Status;
    XTtcPs_Config *Config;
    XTtcPs *Timer;
    TmrCntrSetup *TimerSetup;

    TimerSetup = &SettingsTable[DeviceID];
    Timer = &(TtcPsInst[DeviceID]);

    Config = XTtcPs_LookupConfig(DeviceID);
    if (NULL == Config) {
        return XST_FAILURE;
    }

    Status = XTtcPs_CfgInitialize(Timer, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    XTtcPs_SetOptions(Timer, TimerSetup->Options);

    // If no values given calculate them
    if ((TimerSetup->Prescaler == 0) && (TimerSetup->Interval == 0)) {
        /*
         * Timer frequency is preset in the TimerSetup structure,
         * however, the value is not reflected in its other fields, such as
         * IntervalValue and PrescalerValue. The following call will map the
         * frequency to the interval and prescaler values.
         */
        XTtcPs_CalcIntervalFromFreq(Timer, TimerSetup->OutputHz,
            &(TimerSetup->Interval), &(TimerSetup->Prescaler));
    }

    XTtcPs_SetInterval(Timer, TimerSetup->Interval);
    XTtcPs_SetPrescaler(Timer, TimerSetup->Prescaler);

    return XST_SUCCESS;
}

static int bsp_timer_init_irq(uint32_t ttc_device_id, uint32_t ttc_tick_intr_id)
{
    int Status;
    XTtcPs *TtcPsTick;

    TtcPsTick = &(TtcPsInst[ttc_device_id]);

    Status = XScuGic_Connect(gic_inst_p, ttc_tick_intr_id,
        (Xil_ExceptionHandler)XTtcPs_InterruptHandler, (void *)TtcPsTick);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    XTtcPs_SetStatusHandler(&(TtcPsInst[ttc_device_id]), &(TtcPsInst[ttc_device_id]),
                      (XTtcPs_StatusHandler)TickHandler);
    XScuGic_Enable(gic_inst_p, ttc_tick_intr_id);
    XTtcPs_EnableInterrupts(TtcPsTick, XTTCPS_IXR_INTERVAL_MASK);

    return Status;
}

/*-------------------------------------------------------------------
 * Global functions
 *-----------------------------------------------------------------*/
__attribute__((__weak__)) void timer_irq_callback__(void)
{
    // This function must be implemented by user to use this abstraction layer
    static uint32_t div_cnt = 0;
    div_cnt++;
    if (div_cnt >= 10000) {
        div_cnt = 0;

        static uint8_t cnt = 0;
        cnt++;
        xil_printf("%s(): %d\n", __func__, cnt);
    }
}

void bsp_timer_init(void)
{
    xil_printf("%s()\n", __func__);

    if (bsp_timer_init_ip(TTC_TICK_DEVICE_ID) != XST_SUCCESS)
        xil_printf("ERROR: %s() failed\n", "bsp_timer_init_irq");

    if (bsp_timer_init_irq(TTC_TICK_DEVICE_ID, TTC_TICK_INTR_ID) != XST_SUCCESS)
        xil_printf("ERROR: %s() failed\n", "bsp_timer_init_irq");

    if (bsp_timer_init_ip(TTC_TIMESTAMP_DEVICE_ID) != XST_SUCCESS)
        xil_printf("ERROR: %s() failed\n", "bsp_timer_init_irq");
}

void bsp_timer_start(void)
{
    xil_printf("%s()\n", __func__);

    XTtcPs_Start(&TtcPsInst[TTC_TICK_DEVICE_ID]);
    XTtcPs_Start(&TtcPsInst[TTC_TIMESTAMP_DEVICE_ID]);
}

void bsp_timer_stop(void)
{
    xil_printf("%s()\n", __func__);

    XTtcPs_Stop(&TtcPsInst[TTC_TICK_DEVICE_ID]);
    XTtcPs_Stop(&TtcPsInst[TTC_TIMESTAMP_DEVICE_ID]);
}

uint16_t bsp_timer_timestamp_get(void)
{
    return XTtcPs_GetCounterValue(&TtcPsInst[TTC_TIMESTAMP_DEVICE_ID]);
}

float bsp_timer_timestamp_get_time_delta_us(uint16_t time_start,
                                            uint16_t time_end)
{
    uint16_t time_delta = (time_end - time_start);
    float time_passed_us = (((float)time_delta * (float)1e6)
            / SettingsTable[TTC_TIMESTAMP_DEVICE_ID].OutputHz);
    return time_passed_us;
}
