#include "xparameters.h"	/* XPAR parameters */
#include "xspi.h"		/* SPI device driver */
#include "xspi_l.h"
#include "xil_printf.h"


int SpiPolledExample(XSpi *SpiInstancePtr, u16 SpiDeviceId);
void start_trans(XSpi *SpiInstancePtr);
