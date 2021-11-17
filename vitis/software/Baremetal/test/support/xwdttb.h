#ifndef XWDTTB_H		/* prevent circular inclusions */
#define XWDTTB_H		/* by using protection macros */

/***************************** Include Files *********************************/


// #include <stdint.h>
#include "xil_types.h"
// #include "xil_assert.h"
// #include "xstatus.h"
// #include "xwdttb_l.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/

// typedef uint32_t u32;

/**
 * This typedef contains enumeration of different events in basic mode.
 */
typedef enum {
	XWDTTB_NO_BAD_EVENT = 0,	/**< No bad event */
	XWDTTB_RS_KICK_EVENT,		/**< Restart kick or disable attempt in
					  *  first window */
	XWDTTB_TSR_MM_EVENT,		/**< TSR mismatch */
	XWDTTB_SEC_WIN_EVENT		/**< Second window overflow */
} XWdtTb_Event;

/**
 * This typedef contains configuration information for the device.
 */
typedef struct {
	u16 DeviceId;		/**< Unique ID of the device */
	UINTPTR BaseAddr;	/**< Base address of the device */
	u32 EnableWinWdt;	/**< Flag for Window WDT enable */
	u32 MaxCountWidth;	/**< Maximum width of first timer */
	u32 SstCountWidth;	/**< Maximum width of Second Sequence Timer */
	u32 IsPl;		/**< IsPl, 1= AXI Timebase ,0= WWDT  */
} XWdtTb_Config;

/**
 * The XWdtTb driver instance data. The user is required to allocate a
 * variable of this type for every watchdog/timer device in the system.
 * A pointer to a variable of this type is then passed to the driver API
 * functions.
 */
typedef struct {
	XWdtTb_Config Config;	/**< Hardware Configuration */
	u32 IsReady;		/**< Device is initialized and ready */
	u32 IsStarted;		/**< Device watchdog timer is running */
	u32 EnableFailCounter;	/**< Fail counter, 0 = Disable, 1 = Enable */
    u32 EnableWinMode;      /**<Enable Window WDT Method,0= DIsable,1=Enable*/
} XWdtTb;

/***************** Macros (Inline Functions) Definitions *********************/
/*****************************************************************************/
/**
* @brief
*
* This function returns the current contents of the timebase.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return	The contents of the timebase.
*
* @note		None.
*
******************************************************************************/
u32 XWdtTb_GetTbValue(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 0U);

	// /* Return the contents of the timebase register */
	// return XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_TBR_OFFSET);
	return 0L;
}
/*****************************************************************************/
/**
* @brief
*
* This function controls the read/write access to the complete Window WDT
* register space.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
* @param	AccessMode specifies a value that needs to be used to provide
*		read/write access to the register space.
*		- 1 = Window WDT register space is writable.
*		- 0 = Window WDT register space is read only.
*
* @return	None.
*
* @note		When register space is set read only, writes to any register
*		are ignored and does not lead to good or bad event generation.
*
******************************************************************************/
void XWdtTb_SetRegSpaceAccessMode(const XWdtTb *InstancePtr,
						u32 AccessMode)
{
	// /* Verify arguments. */
	// Xil_AssertVoid(InstancePtr != NULL);
	// Xil_AssertVoid(InstancePtr->EnableWinMode == 1U);
	// Xil_AssertVoid((AccessMode == 0U) || (AccessMode == 1U));

	// /* Write access mode */
	// XWdtTb_WriteReg(InstancePtr->Config.BaseAddr, XWT_MWR_OFFSET,
	// 	AccessMode);
}

/*****************************************************************************/
/**
* @brief
*
* This function provides Window WDT register space read only or writable.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return
*		- 1 = Window WDT register space is writable.
*		- 0 = Window WDT register space is read only.
*
* @note		None.
*
******************************************************************************/
u32 XWdtTb_GetRegSpaceAccessMode(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

	// /* Read master write control register and return register space read
	//  * only or writable
	//  */
	// return (XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_MWR_OFFSET) &
	// 	XWT_MWR_MWC_MASK);
	return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function provides the last bad event and read even after system reset.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return	One of the enumeration value described in XWdtTb_Event.
*
* @note		Event can be read after a system reset to determine if the
*		reset was caused by a watchdog timeout.
*
******************************************************************************/
u32 XWdtTb_GetLastEvent(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

	// /* Read enable status register and return last bad event(s) */
	// return ((XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_ESR_OFFSET) &
	// 	XWT_ESR_LBE_MASK) >> XWT_ESR_LBE_SHIFT);
	return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function provides fail count value.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return	Fail counter value. The default value is 5.
*
* @note
*		- When fail counter is enabled, it gets incremented for every
*		bad event unless 7 or decrement ed for every good event unless
*		0. If fail counter is 7 and another bad event happens, reset is
*		generated.
*		- When fail counter is disabled, bad event leads to reset.
*
******************************************************************************/
u32 XWdtTb_GetFailCounter(const XWdtTb *InstancePtr)
{

// 	/* Verify arguments. */
// 	Xil_AssertNonvoid(InstancePtr != NULL);
// 	Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

// 	/* Read enable status register and return fail counter value */
// 	return ((XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_ESR_OFFSET) &
// 		XWT_ESR_FCV_MASK) >> XWT_ESR_FCV_SHIFT);
return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function states that whether the reset is pending or not when Secondary
* Sequence Timer(SST) counter has started.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return
*		- 1 = window watchdog reset is pending.
*		- 0 = window watchdog reset is not pending.
*
* @note		None.
*
******************************************************************************/
u32 XWdtTb_IsResetPending(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

	// /* Read enable status register and return reset pending bit */
	// return ((XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_ESR_OFFSET) &
	// 	XWT_ESR_WRP_MASK) >> XWT_ESR_WRP_SHIFT);
	return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function states that whether window watchdog timer has reached at the
* interrupt programmed point in second window.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return
*		- 1 = when window watchdog timer has reached at the interrupt
*		programmed point in second window.
*		- 0 = when window watchdog timer did not reach at the
*		 interrupt programmed point in second window.
*
* @note		None.
*
******************************************************************************/
u32 XWdtTb_GetIntrStatus(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

	// /* Read enable status register and return interrupt status */
	// return ((XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_ESR_OFFSET) &
	// 	XWT_ESR_WINT_MASK) >> XWT_ESR_WINT_SHIFT);
	return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function states wrong configuration when second window count is set to
* zero.
*
* @param	InstancePtr is a pointer to the XWdtTb instance to be
*		worked on.
*
* @return
*		- 1 = if second window count is set to zero.
*		- 0 = if second window count is not set to zero.
*
* @note		None.
*
******************************************************************************/
u32 XWdtTb_IsWrongCfg(const XWdtTb *InstancePtr)
{
	// /* Verify arguments. */
	// Xil_AssertNonvoid(InstancePtr != NULL);
	// Xil_AssertNonvoid(InstancePtr->EnableWinMode == 1U);

	// /* Read enable status register and return wrong configuration value */
	// return ((XWdtTb_ReadReg(InstancePtr->Config.BaseAddr, XWT_ESR_OFFSET) &
	// 	XWT_ESR_WCFG_MASK) >> XWT_ESR_WCFG_SHIFT);
	return 0L;
}

/*****************************************************************************/
/**
* @brief
*
* This function sets the count value for the  Second Sequence Timer window.
*
* @param     InstancePtr is a pointer to the XWdtTb instance to be
*            worked on.
* @param     SST_window_config specifies the first window count value.
*
* @return    None.
*
* @note
*            This function must be called before Window WDT start/enable
*            or after Window WDT stop/disable.
*            - For SSTWR window, This option provides additional time to software
*              by delaying the inevitable wwdt_reset assertion/generation by
*              SC count delay
*
******************************************************************************/

void XWdtTb_SetSSTWindow(const XWdtTb *InstancePtr, u32 SST_window_config)
{
        // /* Verify arguments. */
        // Xil_AssertVoid(InstancePtr != NULL);
        // Xil_AssertVoid(InstancePtr->EnableWinMode == (u32)TRUE);

        // /*  Write SST window count value */
        // XWdtTb_WriteReg(InstancePtr->Config.BaseAddr, XWT_SSTWR_OFFSET,SST_window_config);
}

/*****************************************************************************/
/**
* @brief
*
* This function set configure WDT mode.
*
* @param     InstancePtr is a pointer to the XWdtTb instance to be
*            worked on.
* @param     Mode specifies the GWDT or WWDT. 0 for GWDT and 1 for WWDT.
*
* @return    -XST_SUCESS, if Mode with in the range.
*			 -XST_FAILURE,if Mode is out side of range.
*
******************************************************************************/

u32 XWdtTb_ConfigureWDTMode(XWdtTb *InstancePtr, u32 Mode)
{
	// Xil_AssertNonvoid(InstancePtr != NULL);

	// if ((Mode == (u32) 0) || (Mode == (u32)1)) {
	// 	InstancePtr->EnableWinMode = Mode;
	// 	return XST_SUCCESS;
	// } else {
	// 	return XST_FAILURE;
	// }
	return 0L;
}

/************************** Function Prototypes ******************************/

/*
 * Required functions in xwdttb.c
 */
 s32 XWdtTb_CfgInitialize(XWdtTb *InstancePtr, const XWdtTb_Config *CfgPtr,
				UINTPTR EffectiveAddr);

s32 XWdtTb_Initialize(XWdtTb *InstancePtr, u16 DeviceId);

void XWdtTb_Start(XWdtTb *InstancePtr);

s32 XWdtTb_Stop(XWdtTb *InstancePtr);

u32 XWdtTb_IsWdtExpired(const XWdtTb *InstancePtr);
u32 XWdtTb_IsGenericWdtFWExpired(const XWdtTb *InstancePtr);

void XWdtTb_RestartWdt(const XWdtTb *InstancePtr);

XWdtTb_Config *XWdtTb_LookupConfig(u16 DeviceId);

/* Window WDT functions implemented in xwdttb.c */
void XWdtTb_AlwaysEnable(const XWdtTb *InstancePtr);
void XWdtTb_ClearLastEvent(const XWdtTb *InstancePtr);
void XWdtTb_ClearResetPending(const XWdtTb *InstancePtr);
void XWdtTb_IntrClear(const XWdtTb *InstancePtr);

void XWdtTb_SetByteCount(const XWdtTb *InstancePtr, u32 ByteCount);
u32 XWdtTb_GetByteCount(const XWdtTb *InstancePtr);
void XWdtTb_SetByteSegment(const XWdtTb *InstancePtr, u32 ByteSegment);
u32 XWdtTb_GetByteSegment(const XWdtTb *InstancePtr);
void XWdtTb_EnableSst(const XWdtTb *InstancePtr);
void XWdtTb_DisableSst(const XWdtTb *InstancePtr);
void XWdtTb_EnablePsm(const XWdtTb *InstancePtr);
void XWdtTb_DisablePsm(const XWdtTb *InstancePtr);
void XWdtTb_EnableFailCounter(XWdtTb *InstancePtr);
void XWdtTb_DisableFailCounter(XWdtTb *InstancePtr);
void XWdtTb_EnableExtraProtection(const XWdtTb *InstancePtr);
void XWdtTb_DisableExtraProtection(const XWdtTb *InstancePtr);

void XWdtTb_SetWindowCount(const XWdtTb *InstancePtr, u32 FirstWinCount,
				u32 SecondWinCount);
void XWdtTb_SetGenericWdtWindow(const XWdtTb *InstancePtr, u32 GWOR_config);
u32 XWdtTb_ProgramWDTWidth(const XWdtTb *InstancePtr, u32 width);

/*
 * Self-test functions in xwdttb_selftest.c
 */
s32 XWdtTb_SelfTest(const XWdtTb *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/** @} */
