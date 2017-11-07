/*------------------------------------------------------------------------------------------------------------------
--  SOURCE FILE: dcgps.cpp - An application that will connect to local GPS dongle to read satellite data and display the time and coordinates of 
-- 							the user and information about the connected satellites
--
--  PROGRAM:	Assignment 3
--
--  FUNCTIONS:
--				int main(void)
--
--  DATE:		November 2, 2017
--
--  REVISIONS:	(Date and Description)
--
--  DESIGNER:	Matthew Shew, Anthony Vu
--
--  PROGRAMMER: Matthew Shew, Anthony Vu
--
--  NOTES:
--  The program will detect for local RFID devices and attempt to connect to the RFID device. The RFID will be set to read 
--  mode and will listen constantly for any nearby tags. When a tag comes in proximity of the RFID, the RFID will read the 
--  tag info and the program will print the tag info to the screen. When a user disconnects the RFID the program will 
--  release any handles to connected devices and be ready to connect to another RFID device when prompted. If a user selects 
-- "quit" the the program will release any handles to connected devices and the program will terminate closing the application window. 
--
----------------------------------------------------------------------------------------------------------------------*/

#include "header.h"
#include "gps-utils.h"


/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:	main
--
--  DATE:			October 15, 2017
--
--  REVISIONS:
--
--  DESIGNER:		
--
--  PROGRAMMER:		
--
--  INTERFACE:		int main(void)
--
--  RETURNS:		Returns an int value based on function's success. 
--						
--
--  NOTES:
--  This function is the entry point into the program, and creates the data structures and port for the program.
--  Initial setup and shutdown are controlled by this function. 
----------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
	static struct fixsource_t source;
	static struct gps_data_t *gpsdata;
	gpsdata = malloc(sizeof(struct gps_data_t));
	memset(gpsdata, 0, (sizeof(struct gps_data_t)));
	
	
	source.server = LOCAL_HOST;
	source.port = DEFAULT_GPSD_PORT;
	source.device = NULL;

	if(gps_open(source.server, source.port, gpsdata) == -1) {
		printf("gps_open failed\n");
	} 
	
	
	gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

	readGpsData(gpsdata);

	free(gpsdata);
	gps_close(gpsdata);
	return 0;
}

