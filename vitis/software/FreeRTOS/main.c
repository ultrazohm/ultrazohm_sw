/******************************************************************************
* Copyright 2021-2023 Sebastian Wendel, Eyke Liegmann, Martin Geier
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "xparameters.h"
#include "netif/xadapter.h"

//Includes for Ethernet
#if LWIP_DHCP==1
 #include "lwip/dhcp.h"
#endif

//Includes for CAN
#define CAN_ACTIVE 0 // (1 = CAN is active)  and (0 = CAN is inactive)
#include "include/can.h"

//Includes from own files
#include "main.h"
#include "defines.h"
#include "include/isr.h"
#include "uz/uz_PLATFORM/uz_platform.h"
#include "uz/uz_PHY_reset/uz_phy_reset.h"


size_t lifecheck_mainThread = 0;
size_t lifeCheck_networkThread = 0;

// APU-local "mirror" of RPU status word: Written in isr.c, read below in i2cio_thread
uint32_t javascope_data_status = 0;

#if LWIP_DHCP==1
 extern volatile int dhcp_timoutcntr;
 err_t dhcp_start(struct netif *netif);
 #if ( DHCP_FINE_TIMER_MSECS != NETWORK_LOOPPERIOD_MS )
  #warning Unexpected value in DHCP_FINE_TIMER_MSECS, you might want to check this and adapt NETWORK_LOOPPERIOD_MS afterwards
 #endif
#else
 #define DHCP_FINE_TIMER_MSECS NETWORK_LOOPPERIOD_MS
#endif

static struct netif server_netif;

//==============================================================================================================================================================
void print_ip(char *msg, ip_addr_t *ip)
{
	uz_printf(msg);
	uz_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

//==============================================================================================================================================================
void print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw){

	print_ip("Board IP: ", ip);
	print_ip("Netmask : ", mask);
	print_ip("Gateway : ", gw);
}


#include "APU_RPU_shared.h"
#include "xil_cache.h"

enum init_chain
{
	initialization_handshake = 0,
	initialization_rtos
};
enum init_chain initialization_chain = initialization_handshake;

uint32_t apu_version_final = 0U;
uint32_t rpu_version_final = 0U;
uint32_t rpu_default_version = 0U;

int main()
{
	switch (initialization_chain)
	{
		case initialization_handshake:
			write_apu_version(257U);
			do
			{
				rpu_version_final = read_rpu_version();
			} while (!(rpu_version_final == 0U));
			do
			{
				rpu_version_final = read_rpu_version();
			} while ((rpu_version_final == 0U));
			rpu_default_version = rpu_version_final;
			uz_assert( UZ_SUCCESS == uz_platform_init(rpu_default_version) );
			apu_version_final = uz_platform_get_hw_revision();
			write_apu_version(apu_version_final);
			do
			{
				rpu_version_final = read_rpu_version();
			} while (!(apu_version_final == rpu_version_final));

#if (UZ_PLATFORM_CARDID==1)
 {
			const uint32_t card_slots = UZ_PLATFORM_I2CADDR_UZCARDEEPROM_LAST - UZ_PLATFORM_I2CADDR_UZCARDEEPROM_BASE + 1;

			uz_printf("\r\n--- Adapter Card ID:\r\n\r\n");

			for (uint32_t i=0; i<card_slots; i++) {
				uz_platform_eeprom_group000models_t model = 1000;		// Groups are defined up to 999,
				uint8_t revision = 0;									// whilst revisions and
				uint16_t serial = 0;									// serials start at one

				if ( UZ_SUCCESS == uz_platform_cardread(i, &model, &revision, &serial) )
					uz_printf("Board model/revision/serial of adapter card in slot %i: %03i/%02i/%04i\r\n", i, model, revision, serial);
				else
					uz_printf("Identification of adapter card in slot %i failed (no PCB or EEPROM)\r\n", i);

				uz_printf("\r\n");
			}

			uz_printf("---\r\n\r\n");
 }
#endif
		initialization_chain = initialization_rtos;


		case initialization_rtos:
			// SW: Initialize the Interrupts in the main, because by doing it in the network-threat, there were always problems that the thread was killed.
			Initialize_InterruptHandler();

			// Start the main-threat
			sys_thread_new("main_thrd", (void (*)(void *))main_thread, 0,
						   THREAD_STACKSIZE,
						   DEFAULT_THREAD_PRIO);
			vTaskStartScheduler();
			break;
	}
	uz_printf("APU: Error in scheduler");

	return 0;
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  network_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Initializes the InterruptServiceRoutine (ISR) in order to enable a
 *      Data transfer between the both processors in a deterministic time
 *      period. Afterwards the network thread enables the basic send and receive
 *      functions for the Ethernet/TCP communication with the receive thread
 *      "xemacif_input_thread()". This thread runs always!
 *---------------------------------------------------------------------------*/
void network_thread(void *p)
{
	// Initialize the Interrupts
	Initialize_ISR();

    struct netif *netif;
    /* the mac address of the board. this should be unique per board */
    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
    if ( XST_SUCCESS != uz_platform_macread_primary(mac_ethernet_address) )
        uz_printf("APU: Error fetching MAC address from EEPROM, using default\r\n");

#if LWIP_IPV6==0
    ip_addr_t ipaddr, netmask, gw;
#if LWIP_DHCP==1
    int mscnt = 0;
#endif
#endif

    netif = &server_netif;

    uz_printf("\r\n\r\n");
    uz_printf("APU: Network thread started\r\n");

#if LWIP_IPV6==0
#if LWIP_DHCP==0
    /* initialize IP addresses to be used */
    IP4_ADDR(&ipaddr,  192, 168, 1, 233);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      192, 168, 1, 1);
#endif

    /* print out IP settings of the board */

#if LWIP_DHCP==0
    print_ip_settings(&ipaddr, &netmask, &gw);
    /* print all application headers */
#endif

#if LWIP_DHCP==1
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#endif
#endif

    /* Add network interface to the netif_list, and set it as default */
    if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
		uz_printf("APU: Error adding N/W interface\r\n");
		return;
    }

    netif_set_default(netif);

    /* specify that the network if is up */
    netif_set_up(netif);

    /* start packet receive thread - required for lwIP operation */
    sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, netif,
            THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);

#if CAN_ACTIVE==1
	uz_printf(" Init CAN \n\r"); //CAN interface
	//hal_can_init(XPAR_PSU_CAN_0_BASEADDR, XPAR_PSU_CAN_0_DEVICE_ID); //CAN 0 interface
	hal_can_init(XPAR_PSU_CAN_1_BASEADDR, XPAR_PSU_CAN_1_DEVICE_ID); //CAN 1 interface

	can_frame_t can_frame_rx; //CAN interface
#endif

/*	// Enable (currently not required for I²C-based GPOs)
	uz_platform_gposet(I2CLED_FPRING, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD10GREEN, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD11RED, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD12YELLOW, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD13BLUE, UZP_GPO_ENABLE2PUSHPULLED);
*/
	// Set
	uz_platform_gposet(I2CLED_FPRING, UZP_GPO_ASSERT_QUEUED);
	uint8_t mz_lscan = 0;
	uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_DEASSERT_QUEUED);
	uz_platform_gposet(I2CLED_MZD13BLUE,	UZP_GPO_DEASSERT_QUEUED);

#if LWIP_DHCP==1
    dhcp_start(netif);
    // Remaining DHCP handling (apart from its periodic timers, cf. below) and start of application_thread are performed in main_thread
#else
    uz_printf("\r\n");
    uz_printf("%20s %6s %s\r\n", "Server", "Port", "Connect With..");
    uz_printf("%20s %6s %s\r\n", "--------------------", "------", "--------------------");

    print_echo_app_header();
    uz_printf("\r\n");
    sys_thread_new("echod", application_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);
#endif

    // Periodic (cf. DHCP_FINE_TIMER_MSECS) loop for "all things networking" (i.e., Ethernet DHCP and CAN demo)
    while (1) {

#if LWIP_DHCP==1
    	lifeCheck_networkThread++;
      	if(lifeCheck_networkThread > 2500){
      		lifeCheck_networkThread =0;
      	}

		dhcp_fine_tmr();
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >= DHCP_COARSE_TIMER_SECS*1000) {
			dhcp_coarse_tmr();
			mscnt = 0;
		}
#endif

#if CAN_ACTIVE==1
		if( ! hal_can_is_rx_empty() ){
			hal_can_receive_frame_blocking(&can_frame_rx);
			if(can_frame_rx.std_id == 0x22) {
			//	XcpCommand( (uint32_t *) can_frame_rx.data );
				can_send_2();
			} else {

				//hal_can_debug_print_frame(&can_frame_rx);
				//uz_printf("received a not XCP related CAN frame \n\r");
			}
			//usleep(1000 * 500);
		}else{
			can_send_1();
			//usleep(1000 * 500);
		}

		// no tx message pending
		if( hal_can_is_tx_done()) {
			//XcpSendCallBack();
		}
#endif

		uz_platform_gposet(I2CLED_FPRING, UZP_GPO_TOGGLE_QUEUED);

		// Toggle LEDs on MZ sequentially
		switch(mz_lscan)
		{
			default:
				uz_platform_gposet(I2CLED_MZD11RED,		UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD10GREEN,	UZP_GPO_ASSERT_QUEUED);
				mz_lscan = 0;
				break;
			case 1:
				uz_platform_gposet(I2CLED_MZD10GREEN,	UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD11RED,		UZP_GPO_ASSERT_QUEUED);
				break;
			case 2:
				uz_platform_gposet(I2CLED_MZD11RED,		UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_ASSERT_QUEUED);
				break;
			case 3:
				uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD13BLUE,	UZP_GPO_ASSERT_QUEUED);
				break;
			case 4:
				uz_platform_gposet(I2CLED_MZD13BLUE,	UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_ASSERT_QUEUED);
				break;
			case 5:
				uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_DEASSERT_QUEUED);
				uz_platform_gposet(I2CLED_MZD11RED,		UZP_GPO_ASSERT_QUEUED);
				break;
		}
		mz_lscan++;

		vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);

	}	// endless while(1)

    return;
}

void i2cio_thread()
{
/*	// Enable
	uz_platform_gposet(I2CLED_FP1RDY, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_FP2RUN, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_FP3ERR, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_FP4USR, UZP_GPO_ENABLE2PUSHPULLED);
*/
	while(1) {
		// Mirror "UltraZohm LEDs" (cf. Baremetal/src/sw/javascope.c) to I²C-LEDs
		if (apu_version_final > 4U)
		{
			// Mirror "UltraZohm LEDs" (cf. Baremetal/src/sw/javascope.c) to I²C-LEDs
			uz_platform_gposet(I2CLED_FP1RDY, (javascope_data_status & (1 << 0)) ? UZP_GPO_ASSERT_QUEUED : UZP_GPO_DEASSERT_QUEUED);
			uz_platform_gposet(I2CLED_FP2RUN, (javascope_data_status & (1 << 1)) ? UZP_GPO_ASSERT_QUEUED : UZP_GPO_DEASSERT_QUEUED);
			uz_platform_gposet(I2CLED_FP3ERR, (javascope_data_status & (1 << 2)) ? UZP_GPO_ASSERT_QUEUED : UZP_GPO_DEASSERT_QUEUED);
			uz_platform_gposet(I2CLED_FP4USR, (javascope_data_status & (1 << 3)) ? UZP_GPO_ASSERT_QUEUED : UZP_GPO_DEASSERT_QUEUED);

			// Push all (I²C-)GPO changes to hardware
			uz_platform_gpoupdate();
		}

		vTaskDelay(I2CIO_THREAD_TIMER_MS / portTICK_RATE_MS);

	}	// endless while(1)
}

//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  main_thread
 *---------------------------------------------------------------------------*
 * Description:
 *      Starts the network thread "network_thread()" with priority
 *      "DEFAULT_THREAD_PRIO". Afterwards the main thread starts and builds up
 *      the Ethernet communication. If it is not possible after a couple of
 *      seconds, a time-out will occur. If a communication is possible, the
 *      application thread "application_thread()" will be started.
 *      This thread runs only until the LifeCheck counter receives the value of 20
 *      with a step size of 0.25 second = 5 seconds (500us * 10000).
 *      This is also the time for the time-out (if no connection is available).
 *---------------------------------------------------------------------------*/
int main_thread()
{
#if LWIP_DHCP==1
	int mscnt = 0;
#endif

	uz_printf("APU Build Date: %s at %s,\r\n",__DATE__, __TIME__);

	// reset phy
	uz_phy_reset();

	/* initialize lwIP before calling sys_thread_new */
    lwip_init();

    /* any thread using lwIP should be created using sys_thread_new */
    //Open thread for Ethernet communication
    sys_thread_new("NW_THRD", network_thread, NULL,
		THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);


#if LWIP_DHCP==1
    while (1) {

		lifecheck_mainThread++;
		if(lifecheck_mainThread > 2500){
			lifecheck_mainThread =0;
		}

		vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);

		if (server_netif.ip_addr.addr) {
			uz_printf("APU: DHCP request success\r\n");
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));

			break;
		}
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >=7500) { // define timeout time here
			uz_printf("APU: DHCP request timed out\r\n");
			uz_printf("APU: Configuring default IP of 192.168.1.233\r\n");
			IP4_ADDR(&(server_netif.ip_addr),  192, 168, 1, 233);
			IP4_ADDR(&(server_netif.netmask), 255, 255, 255,  0);
			IP4_ADDR(&(server_netif.gw),  192, 168, 1, 1);
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
			/* print all application headers */
			uz_printf("\r\n");
			uz_printf("%20s %6s %s\r\n", "Server", "Port", "Connect With..");
			uz_printf("%20s %6s %s\r\n", "--------------------", "------", "--------------------");

			break;
		}
	}	// while(1)

	print_echo_app_header();
	uz_printf("\r\n");

	sys_thread_new("echod", application_thread, 0,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);
#endif

	sys_thread_new("i2cio", i2cio_thread, 0,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);

    vTaskDelete(NULL);
    return 0;
}



//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  hal_can_debug_print_frame
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void hal_can_debug_print_frame(can_frame_t *can_frame_p)
{
	uz_printf("std_id: 0x%03X, dlc: %d, data[0]: 0x%02X \n\r",
			can_frame_p->std_id, can_frame_p->dlc, can_frame_p->data[0]);
}


//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  can_send_1
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void can_send_1(void)
{
	static uint8_t tick;
	tick++;
	if(tick > 250){
		tick =0;
	}

	//uz_printf("tick: 0x%02X \n\r", tick);
	//Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR, tick);

	can_frame_t can_frame_tx;
	can_frame_tx.std_id = 0x123;
	can_frame_tx.dlc = 2;
	can_frame_tx.data[0] = 0x13;
	can_frame_tx.data[1] = tick;

	hal_can_send_frame_blocking(&can_frame_tx);
}


//==============================================================================================================================================================
/*---------------------------------------------------------------------------*
 * Routine:  can_send_2
 *---------------------------------------------------------------------------*
 * Description:
 *      CAN interface for testing
 *---------------------------------------------------------------------------*/
void can_send_2(void)
{
	static uint8_t tick;
	tick=tick+10;
	if(tick > 250){
		tick =0;
	}

	//uz_printf("tick: 0x%02X \n\r", tick);
	//Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR, tick);

	can_frame_t can_frame_tx;
	can_frame_tx.std_id = 0x52;
	can_frame_tx.dlc = 2;
	can_frame_tx.data[0] = 0x12;
	can_frame_tx.data[1] = tick;

	hal_can_send_frame_blocking(&can_frame_tx);
}
