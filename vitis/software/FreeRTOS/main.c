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

//Includes from own files
#include "main.h"
#include "defines.h"
#include "include/isr.h"
#include "uz/uz_PLATFORM/uz_platform.h"
#include "uz/uz_PHY_reset/uz_phy_reset.h"

#include "uz/uz_can/uz_can.h"
#include "include/can.h"

struct uz_can_config_t can_config_0 = {
	.base_address = XPAR_PSU_CAN_0_BASEADDR,
	.ip_core_frequency_Hz = 100000000U, // 100 MHz
	.can_device_id = XPAR_PSU_CAN_0_DEVICE_ID};

struct uz_can_config_t can_config_1 = {
	.base_address = XPAR_PSU_CAN_1_BASEADDR,
	.ip_core_frequency_Hz = 100000000U, // 100 MHz
	.can_device_id = XPAR_PSU_CAN_1_DEVICE_ID};

uz_can_t* can_instance_0 = NULL;
uz_can_t* can_instance_1 = NULL;


size_t lifecheck_mainThread = 0;
size_t lifeCheck_networkThread = 0;

// APU-local mirror of the RPU status word; used by i2cio_thread if LED mirroring is enabled.
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
static void print_ip(const char *label, ip_addr_t *ip)
{
	uz_printf("%s", label);
	uz_printf("%d.%d.%d.%d\r\n", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

//==============================================================================================================================================================
static void print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw){

	print_ip("APU: Board IP: ", ip);
	print_ip("APU: Netmask : ", mask);
	print_ip("APU: Gateway : ", gw);
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

				if ( UZ_SUCCESS == uz_platform_cardread(i, &model, &revision, &serial) ) {
					uz_printf("Board model/revision/serial of adapter card in slot %i: %03i/%02i/%04i\r\n", i, model, revision, serial);

					if ( (UZP_HWGROUP_ADCARD_DIGVOLT335 == model) && (1 < revision) )
						uz_platform_configcard_model015_voltageled(i);
				} else
					uz_printf("Identification of adapter card in slot %i failed (no PCB or EEPROM)\r\n", i);

				uz_printf("\r\n");
			}

			uz_printf("---\r\n\r\n");
 }
#endif
		initialization_chain = initialization_rtos;


		case initialization_rtos:
				// Initialize the interrupt handler here in main() rather than in network_thread, to avoid the
				// interrupt handler being registered before the thread stack is fully established.
			Initialize_InterruptHandler();
#if CAN_ACTIVE==1
	uz_printf("APU: Init CAN \r\n"); // CAN interface
	can_instance_0 = uz_can_init(can_config_0); // CAN 0 interface
	can_instance_1 = uz_can_init(can_config_1); // CAN 1 interface

#endif
			// Start the main thread
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
 *      Initializes the A53-side IPI ISR and JavaScope queues, configures the
 *      Ethernet interface, starts the lwIP input thread, and starts the
 *      JavaScope TCP server once an IP address is available.
 *---------------------------------------------------------------------------*/
void network_thread(void *p)
{
	// Initialize the A53-side IPI handler and JavaScope queues.
	Initialize_ISR();

    struct netif *netif;
    /* The MAC address is board-specific; fall back to the Xilinx default if EEPROM read fails. */
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
    uz_printf("APU: Network initialization started\r\n");

#if LWIP_IPV6==0
#if LWIP_DHCP==0
    /* Static IPv4 configuration used when DHCP is disabled. */
    IP4_ADDR(&ipaddr,  192, 168, 1, 233);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      192, 168, 1, 1);
#endif

#if LWIP_DHCP==0
    print_ip_settings(&ipaddr, &netmask, &gw);
#endif

#if LWIP_DHCP==1
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#endif
#endif

    /* Add network interface to the netif_list, and set it as default. */
    uz_printf("\r\nAPU: Initializing Ethernet MAC at 0x%08x\r\n",
            (unsigned int)PLATFORM_EMAC_BASEADDR);
    struct netif *added_netif = xemac_add(netif, &ipaddr, &netmask, &gw,
            mac_ethernet_address, PLATFORM_EMAC_BASEADDR);
    if (added_netif == NULL) {
		uz_printf("APU: Failed to add Ethernet network interface at 0x%08x\r\n",
				(unsigned int)PLATFORM_EMAC_BASEADDR);
		return;
    }
    /*
     * Xilinx lwIP BSP xadapter.c, function xemac_add(), can print
     * "unable to determine type of EMAC" after successful GEM initialization
     * because the xemac_type_emacps case in the generated BSP file
     * vitis/workspace/UltraZohm/psu_cortexa53_0/FreeRTOS_domain/bsp/
     * psu_cortexa53_0/libsrc/lwip211_v1_8/src/contrib/ports/xilinx/
     * netif/xadapter.c:167 falls through to default at line 181.
     */
    uz_printf("APU: Ethernet MAC initialized at 0x%08x "
            "(previous Xilinx BSP EMAC warning is benign if present)\r\n",
            (unsigned int)PLATFORM_EMAC_BASEADDR);

    netif_set_default(netif);

    /* Enable the interface in lwIP; physical link state is tracked separately by the BSP. */
    netif_set_up(netif);

    /* start packet receive thread - required for lwIP operation */
    sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, netif,
            THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);

/*	// Enable (currently not required for I²C-based GPOs)
	uz_platform_gposet(I2CLED_FPRING, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD10GREEN, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD11RED, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD12YELLOW, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(I2CLED_MZD13BLUE, UZP_GPO_ENABLE2PUSHPULLED);
*/
	// Initialize heartbeat LED states.
	uz_platform_gposet(I2CLED_FPRING, UZP_GPO_ASSERT_QUEUED);
	uint8_t mz_lscan = 0;
	uz_platform_gposet(I2CLED_MZD12YELLOW,	UZP_GPO_DEASSERT_QUEUED);
	uz_platform_gposet(I2CLED_MZD13BLUE,	UZP_GPO_DEASSERT_QUEUED);

#if LWIP_DHCP==1
    dhcp_start(netif);
    // Remaining DHCP handling (apart from its periodic timers, cf. below) and start of application_thread are performed in main_thread
#else
    print_javascope_app_header(&(server_netif.ip_addr));
    sys_thread_new("javascope_tcp", application_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);
#endif

    // Periodic loop for DHCP timers and heartbeat LEDs.
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
		if (apu_version_final > 4U)					// FIXME: Support for MZ broken due to 18e978be1f5dfa2002753cfec87ef567094f8594 ff.
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
 *      Resets the PHY, initializes lwIP, and starts the network thread
 *      "network_thread()". If DHCP is enabled, waits up to 7.5 s for a
 *      lease and then starts the TCP application thread. Exits (vTaskDelete)
 *      after all enabled child threads are launched; it does not run
 *      continuously.
 *---------------------------------------------------------------------------*/
int main_thread()
{
#if LWIP_DHCP==1
	int mscnt = 0;
#endif

	uz_printf("\r\nAPU: Build date of main.c: %s %s\r\n", __DATE__, __TIME__);

	// Reset PHY before lwIP initializes the network interface.
	uz_phy_reset();

	/* initialize lwIP before calling sys_thread_new */
    lwip_init();

    /* Any thread using lwIP should be created using sys_thread_new. */
    // Start Ethernet/DHCP/network-interface handling.
    sys_thread_new("NW_THRD", network_thread, NULL,
		THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);

#if CAN_ACTIVE == 1
	sys_thread_new("CAN_Thread_CAN0", CAN_Thread_CAN0, NULL,
				   THREAD_STACKSIZE,
				   DEFAULT_THREAD_PRIO);
	xil_printf("APU: CAN-Thread0 started\r\n");

	sys_thread_new("CAN_Thread_CAN1", CAN_Thread_CAN1, NULL,
				   THREAD_STACKSIZE,
				   DEFAULT_THREAD_PRIO);

	xil_printf("APU: CAN-Thread1 started\r\n");
#endif

#if LWIP_DHCP==1
    while (1) {

		lifecheck_mainThread++;
		if(lifecheck_mainThread > 2500){
			lifecheck_mainThread =0;
		}

		vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);

		if (server_netif.ip_addr.addr) {
			uz_printf("APU: DHCP request succeeded\r\n");
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));

			break;
		}
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >=7500) { // define timeout time here
			uz_printf("APU: DHCP request timed out; using static fallback IP address 192.168.1.233\r\n");
			IP4_ADDR(&(server_netif.ip_addr),  192, 168, 1, 233);
			IP4_ADDR(&(server_netif.netmask), 255, 255, 255,  0);
			IP4_ADDR(&(server_netif.gw),  192, 168, 1, 1);
			print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
			break;
		}
	}	// while(1)

	print_javascope_app_header(&(server_netif.ip_addr));

	sys_thread_new("javascope_tcp", application_thread, 0,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);
#endif

	/* I2C LED mirroring thread is currently disabled since it runs into assert on Carrierboards Rev>=04
	// TODO: uz_platform needs fixing
	sys_thread_new("i2cio", i2cio_thread, 0,
			THREAD_STACKSIZE,
			DEFAULT_THREAD_PRIO);
*/
    vTaskDelete(NULL);
    return 0;
}
