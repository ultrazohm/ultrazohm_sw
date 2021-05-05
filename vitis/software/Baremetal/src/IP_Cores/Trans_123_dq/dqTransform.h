#include "Trans_123_dq_V12_ip_addr.h"
#include "../../globalData.h"
#include "xparameters.h"
#include "xil_io.h"
#include <stdint.h>
#include "../../defines.h"

//==============================================================================================================================================================
//IP-Block for the 123-dq-Transformation
#define Trans_123_dq_theta_offset_REG 	XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + theta_offset_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_idCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + id_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_iqCurrent_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + iq_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_i1Current_REG		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i1_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset
#define Trans_123_dq_i3Current_REG 		XPAR_TRANS_123_DQ_V12_IP_0_BASEADDR + i3_AXI_Data_Trans_123_dq_V12_ip  //data register for theta_offset

void DQTransformation_Initialize(DS_Data* data);		// Init Park-transformation 123 to dq
