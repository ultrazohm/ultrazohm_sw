#include "../uz_PLATFORM/uz_platform.h"
#include "../uz_HAL.h"
#include "uz_phy_reset.h"

void uz_phy_reset(void)
{
	int phy_reset_high_time_us = 20e3; //20ms = 20,000 us

	// enable apply reset
	uz_platform_gposet(RST_PHY0, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(RST_PHY0, UZP_GPO_DEASSERT);				// DEASSERT -> Drive low (i.e., assert...)

	uz_platform_gposet(RST_PHY1, UZP_GPO_ENABLE2PUSHPULLED);
	uz_platform_gposet(RST_PHY1, UZP_GPO_DEASSERT);				// DEASSERT -> Drive low (i.e., assert...)


	// wait for some time as defined in data sheet
	usleep(phy_reset_high_time_us);

	// release reset and disable MIO pin

	uz_platform_gposet(RST_PHY0, UZP_GPO_ASSERT);				// ASSERT -> Drive high (i.e., deassert...)
	uz_platform_gposet(RST_PHY0, UZP_GPO_DISABLE2TRISTATED);

	uz_platform_gposet(RST_PHY1, UZP_GPO_ASSERT);				// ASSERT -> Drive high (i.e., deassert...)
	uz_platform_gposet(RST_PHY1, UZP_GPO_DISABLE2TRISTATED);


	uz_printf("PHY reset done\r\n");
}



