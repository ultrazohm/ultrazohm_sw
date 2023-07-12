#include <stdio.h>
#include <fcntl.h>	// open
#include <unistd.h>	// close

#define	uz_printf	printf
#include "../FreeRTOS/uz/uz_PLATFORM/uz_platform_eeprom.h"

#define	UZ_PLATFORM_I2CDEV	"/sys/devices/platform/axi/ff030000.i2c/i2c-1/1-"

int main(int argc, char** argv)
{
	printf("This is " __FILE__ " - compiled on " __DATE__ " " __TIME__ " with I2CDEV=\"" UZ_PLATFORM_I2CDEV "\"\n\n");

	uz_platform_eeprom eeprom;

	char devname[sizeof(UZ_PLATFORM_I2CDEV) + 11];
	// For device paths cf. https://www.kernel.org/doc/html/latest/i2c/i2c-sysfs.html#location-of-i2c-sysfs
	snprintf(devname, sizeof(devname)/sizeof(devname[0]), "%s%04x/eeprom", UZ_PLATFORM_I2CDEV, UZ_PLATFORM_I2CADDR_EEPROM);

	int fd;
	fd = open(devname, O_RDWR);
	if (-1 == fd)
	{
		perror("Error opening EEPROM");
		printf("Device was %s, exiting...\n", devname);
		return(1);
	}

	int status;
	off_t offset;

	offset = lseek(fd, UZ_PLATFORM_EEPROM_INFOOFFSET, SEEK_SET);
	if ( UZ_PLATFORM_EEPROM_INFOOFFSET != offset )
	{
		printf("Error seeking (requested %i but got %li), exiting...\n", UZ_PLATFORM_EEPROM_INFOOFFSET, offset);
		close(fd);
		return(2);
	}
	status = read(fd, &eeprom, sizeof(eeprom));
	if ( sizeof(eeprom) != status )
	{
		printf("Error reading (requested %li after seeking to %li, but got %i), exiting...\n", sizeof(eeprom), offset, status);
		close(fd);
		return(3);
	}
	uz_platform_printinfo(&eeprom);

	if (argc > 1)
	{
#if 1
		eeprom.hw_group					= UZP_HWGROUP_UZOHM3;
		eeprom.hw_model					= 1 + UZ_PLATFORM_HWMODEL_EXTOFFSET;	// "UltraZohm Basisgerät" or the like? Further: Non-ZC
		eeprom.fflags_model				= 0b000000;				// Feature flags (unique per model)
		eeprom.hw_revision				= 4;					// Rev04
		eeprom.fflags_revision				= 0b000000;				// Feature flags (unique per model+revision)
		eeprom.serialdata.hw_batchandserial.batch	= 0;					// 
		eeprom.serialdata.hw_batchandserial.serial	= 42;					// 
#else
		eeprom.hw_group					= UZP_HWGROUP_EXTERNAL;
		eeprom.hw_model					= 42;
		eeprom.fflags_model				= 0b000000;				// Feature flags (unique per model)
		eeprom.hw_revision				= 23;
		eeprom.fflags_revision				= 0b000000;				// Feature flags (unique per model+revision)
		eeprom.serialdata.hw_externalserial.extserial	= 654321;
#endif
		printf("\nWriting to EEPROM!\n");
		uz_platform_printinfo(&eeprom);

		offset = lseek(fd, UZ_PLATFORM_EEPROM_INFOOFFSET, SEEK_SET);
		if ( UZ_PLATFORM_EEPROM_INFOOFFSET != offset )
		{
			printf("Error seeking (requested %i but got %li), exiting...\n", UZ_PLATFORM_EEPROM_INFOOFFSET, offset);
			close(fd);
			return(4);
		}
		status = write(fd, &eeprom, sizeof(eeprom));
		if ( sizeof(eeprom) != status )
		{
			printf("Error writing (requested %li after seeking to %li, but got %i), exiting...\n", sizeof(eeprom), offset, status);
			close(fd);
			return(5);
		}
	}

	close(fd);
	return(0);
}
