/******************************************************************************
* FAKEEEE!!!
******************************************************************************/

#ifndef XSCUGIC_H /* prevent circular inclusions */
#define XSCUGIC_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif


/***************************** Include Files *********************************/

#include "xstatus.h"
// #include "xil_types.h"
// #include "xil_io.h"
// #include "xscugic_hw.h"
#include "xil_exception.h"

/************************** Constant Definitions *****************************/

#define EFUSE_STATUS_OFFSET   0x10
#define EFUSE_STATUS_CPU_MASK 0x80

#if !defined (ARMR5) && !defined (__aarch64__) && !defined (ARMA53_32)
#define ARMA9
#endif

#define XSCUGIC500_DCTLR_ARE_NS_ENABLE  0x20
#define XSCUGIC500_DCTLR_ARE_S_ENABLE  0x10

#define XSCUGIC_MAX_NUM_INTR_INPUTS    	195U /* Maximum number of interrupt defined by Zynq Ultrascale Mp */

// typedef void (*Xil_InterruptHandler)(void *data);

/**************************** Type Definitions *******************************/

/* The following data type defines each entry in an interrupt vector table.
 * The callback reference is the base address of the interrupting device
 * for the low level driver and an instance pointer for the high level driver.
 */
typedef struct
{
	// Xil_InterruptHandler Handler;
	void *CallBackRef;
} XScuGic_VectorTableEntry;

/**
 * This typedef contains configuration information for the device.
 */
typedef struct
{
	u16 DeviceId;		/**< Unique ID  of device */
	u32 CpuBaseAddress;	/**< CPU Interface Register base address */
	u32 DistBaseAddress;	/**< Distributor Register base address */
	XScuGic_VectorTableEntry HandlerTable[XSCUGIC_MAX_NUM_INTR_INPUTS];/**<
				 Vector table of interrupt handlers */
} XScuGic_Config;

/**
 * The XScuGic driver instance data. The user is required to allocate a
 * variable of this type for every intc device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
typedef struct
{
	XScuGic_Config *Config;  /**< Configuration table entry */
	u32 IsReady;		 /**< Device is initialized and ready */
	u32 UnhandledInterrupts; /**< Intc Statistics */
} XScuGic;

/***************** Macros (Inline Functions) Definitions *********************/

/****************************************************************************/
/**
*
* Write the given CPU Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XScuGic_CPUWriteReg(XScuGic *InstancePtr, u32 RegOffset, u32 Data)
*
*****************************************************************************/
#define XScuGic_CPUWriteReg(InstancePtr, RegOffset, Data) \
(XScuGic_WriteReg(((InstancePtr)->Config->CpuBaseAddress), (RegOffset), \
					((u32)(Data))))

/****************************************************************************/
/**
*
* Read the given CPU Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XScuGic_CPUReadReg(XScuGic *InstancePtr, u32 RegOffset)
*
*****************************************************************************/
#define XScuGic_CPUReadReg(InstancePtr, RegOffset) \
	(XScuGic_ReadReg(((InstancePtr)->Config->CpuBaseAddress), (RegOffset)))

/****************************************************************************/
/**
*
* Write the given Distributor Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XScuGic_DistWriteReg(XScuGic *InstancePtr, u32 RegOffset, u32 Data)
*
*****************************************************************************/
#define XScuGic_DistWriteReg(InstancePtr, RegOffset, Data) \
(XScuGic_WriteReg(((InstancePtr)->Config->DistBaseAddress), (RegOffset), \
					((u32)(Data))))

/****************************************************************************/
/**
*
* Read the given Distributor Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XScuGic_DistReadReg(XScuGic *InstancePtr, u32 RegOffset)
*
*****************************************************************************/
#define XScuGic_DistReadReg(InstancePtr, RegOffset) \
(XScuGic_ReadReg(((InstancePtr)->Config->DistBaseAddress), (RegOffset)))

/****************************************************************************/
/**
*
* Write the given ReDistributor Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XScuGic_DistWriteReg(XScuGic *InstancePtr, u32 RegOffset, u32 Data)
*
*****************************************************************************/
#define XScuGic_ReDistWriteReg(InstancePtr, RegOffset, Data) \
(XScuGic_WriteReg(((InstancePtr)->Config->DistBaseAddress)+ \
				   XSCUGIC_RDIST_OFFSET, (RegOffset), ((u32)(Data))))

/****************************************************************************/
/**
*
* Read the given ReDistributor Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XScuGic_DistReadReg(XScuGic *InstancePtr, u32 RegOffset)
*
*****************************************************************************/
#define XScuGic_ReDistReadReg(InstancePtr, RegOffset) \
(XScuGic_ReadReg((((InstancePtr)->Config->DistBaseAddress)+ \
XSCUGIC_RDIST_OFFSET), (RegOffset)))

/****************************************************************************/
/**
*
* Write the given ReDistributor SGI PPI Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XScuGic_DistWriteReg(XScuGic *InstancePtr, u32 RegOffset, u32 Data)
*
*****************************************************************************/
#define XScuGic_ReDistSGIPPIWriteReg(InstancePtr, RegOffset, Data) \
(XScuGic_WriteReg(((InstancePtr)->Config->DistBaseAddress)+ \
				   XSCUGIC_RDIST_SGI_PPI_OFFSET, (RegOffset), ((u32)(Data))))

/****************************************************************************/
/**
*
* Read the given ReDistributor SGI PPI Interface register
*
* @param    InstancePtr is a pointer to the instance to be worked on.
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XScuGic_DistReadReg(XScuGic *InstancePtr, u32 RegOffset)
*
*****************************************************************************/
#define XScuGic_ReDistSGIPPIReadReg(InstancePtr, RegOffset) \
(XScuGic_ReadReg((((InstancePtr)->Config->DistBaseAddress)+ \
					XSCUGIC_RDIST_SGI_PPI_OFFSET), (RegOffset)))

/****************************************************************************/
/**
* This function enables system register interface for GIC CPU Interface
*
* @param	value to be written
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_Enable_SystemReg_CPU_Interface_EL3() mtcp(S3_6_C12_C12_5, 0xF);
#define XScuGic_Enable_SystemReg_CPU_Interface_EL1() mtcp(S3_0_C12_C12_5, 0xF);
/****************************************************************************/
/**
* This function enables Grou0 interrupts
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_Enable_Group0_Interrupts() mtcp(S3_0_C12_C12_6,0x1);
/****************************************************************************/
/**
* This function enables Group1 interrupts
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#if defined (__aarch64__)
#if EL1_NONSECURE
#define XScuGic_Enable_Group1_Interrupts() \
		mtcp (S3_0_C12_C12_7, 0x1 | mfcp(S3_0_C12_C12_7) );
#else
#define XScuGic_Enable_Group1_Interrupts() \
		mtcp (S3_6_C12_C12_7, 0x1 | mfcp(S3_6_C12_C12_7) );
#endif
#endif
/****************************************************************************/
/**
* This function writes to ICC_SGI0R_EL1
*
* @param	value to be written
*
* @return	None.
*
* @note     None.
*
*****************************************************************************/
#define XScuGic_WriteICC_SGI0R_EL1(val) mtcp(S3_0_C12_C11_7,val)

/****************************************************************************/
/**
* This function writes to ICC_SGI1R_EL1
*
* @param	value to be written
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_WriteICC_SGI1R_EL1(val) mtcp(S3_0_C12_C11_5,val)

/****************************************************************************/
/**
* This function reads ICC_SGI1R_EL1 register
*
* @param	None
*
* @return	Value of ICC_SGI1R_EL1 register
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_ReadICC_SGI1R_EL1() mfcp(S3_0_C12_C11_5)
/****************************************************************************/
/**
* This function sets interrupt priority filter
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_set_priority_filter(val)  __asm__ __volatile__("msr  S3_0_C4_C6_0,%0"  : : "r" (val))
/****************************************************************************/
/**
* This function returns interrupt id of highest priority pending interrupt
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#if defined (__aarch64__)
#if EL3
#define XScuGic_get_IntID()  mfcp(S3_0_C12_C8_0)
#else
#define XScuGic_get_IntID()  mfcp(S3_0_C12_C12_0)
#endif
#endif
/****************************************************************************/
/**
* This function acks the interrupt
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#if  defined (__aarch64__)
#if EL3
#define XScuGic_ack_Int(val)   mtcp(S3_0_C12_C8_1,val)
#else
#define XScuGic_ack_Int(val)   mtcp(S3_0_C12_C12_1,val)
#endif
#endif
/****************************************************************************/
/**
* This macro returns bit position for the specific interrupt's trigger type
* configuration within GICR_ICFGR0/GICR_ICFGR1 register
*
* @param	None.
*
* @return	None.
*
* @note        None.
*
*****************************************************************************/
#define XScuGic_Get_Rdist_Int_Trigger_Index(IntrId)  (((Int_Id%16) & 0x1f) << 2) +1
/************************** Function Prototypes ******************************/

/*
 * Required functions in xscugic.c
 */

s32  XScuGic_Connect(XScuGic *InstancePtr, u32 Int_Id,
			Xil_InterruptHandler Handler, void *CallBackRef);
void XScuGic_Disconnect(XScuGic *InstancePtr, u32 Int_Id);

void XScuGic_Enable(XScuGic *InstancePtr, u32 Int_Id);
void XScuGic_Disable(XScuGic *InstancePtr, u32 Int_Id);

s32  XScuGic_CfgInitialize(XScuGic *InstancePtr, XScuGic_Config *ConfigPtr,
							u32 EffectiveAddr);

s32  XScuGic_SoftwareIntr(XScuGic *InstancePtr, u32 Int_Id, u32 Cpu_Id);

void XScuGic_GetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id,
					u8 *Priority, u8 *Trigger);
void XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id,
					u8 Priority, u8 Trigger);
void XScuGic_InterruptMaptoCpu(XScuGic *InstancePtr, u8 Cpu_Id, u32 Int_Id);
void XScuGic_InterruptUnmapFromCpu(XScuGic *InstancePtr, u8 Cpu_Id, u32 Int_Id);
void XScuGic_UnmapAllInterruptsFromCpu(XScuGic *InstancePtr, u8 Cpu_Id);
void XScuGic_Stop(XScuGic *InstancePtr);
void XScuGic_SetCpuID(u32 CpuCoreId);
u32 XScuGic_GetCpuID(void);
/*
 * Initialization functions in xscugic_sinit.c
 */
XScuGic_Config *XScuGic_LookupConfig(u16 DeviceId);

/*
 * Interrupt functions in xscugic_intr.c
 */
void XScuGic_InterruptHandler(XScuGic *InstancePtr);

/*
 * Self-test functions in xscugic_selftest.c
 */
s32  XScuGic_SelfTest(XScuGic *InstancePtr);

void XScuGic_EnableSGI_PPI(XScuGic *InstancePtr,u32 ID);
void XScuGic_SetPPI_SGI_Priority(XScuGic *InstancePtr,u32 ID, u32 priority);
#if defined (GICv3)
void XScuGic_MarkCoreAsleep(XScuGic *InstancePtr);
void XScuGic_MarkCoreAwake(XScuGic *InstancePtr);
#endif
#ifdef __cplusplus
}
#endif

#endif            /* end of protection macro */
/** @} */
