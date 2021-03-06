#include "header.h"
#include "gpsprint.h"


/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION: 	printGpsData
--
--  DATE:		November 2, 2017
--
--  REVISIONS:		none
--
--  DESIGNER:		Matthew Shew, Anthony Vu
--
--  PROGRAMMER:		Matthew Shew, Anthony Vu
--
--  INTERFACE:		void printGpsData(struct gps_data_t * gpsdata)
--						struct gps_data_t * gpsdata: The location and satellite info that was returned from the GPS dongle
--
--  RETURNS:		void.
--
--  NOTES:
--  This function is called when a gpsdata structure needs their info to be printed to the screen. Depending on the mode of the gps data that is recieved, 
--  the info printed to the screen will be affected. Mode 3 prints all location, time and satellite data properly, Mode 2 prints the satellite data without elevation, 
--  and Mode 1 prints out n/a for longitude and latitude as a result of too few satellites for a accurate location reading 
----------------------------------------------------------------------------------------------------------------------*/
void printGpsData(struct gps_data_t * gpsdata) {

	bool usedflags[MAXCHANNELS];
	char scr[128];
	printf("----------------------------------\n");
	if (gpsdata->fix.mode >= MODE_2D && isnan (gpsdata->fix.latitude) == 0)
	{
		(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
		fprintf(stdout, "\n%s ", scr);
		fprintf(stdout, "Latitude: %.6f %c; ", (gpsdata->fix.latitude < 0) ? gpsdata->fix.latitude * -1 : gpsdata->fix.latitude, (gpsdata->fix.latitude < 0) ? 'S' : 'N');
		fprintf(stdout, "longitude: %.6f %c; \n\n", (gpsdata->fix.longitude < 0) ? gpsdata->fix.longitude * -1 : gpsdata->fix.longitude, (gpsdata->fix.longitude < 0) ? 'W' : 'E');
		fflush(stdout);
	} 
	else 
	{
		(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
		fprintf(stdout, "\n%s  n/a  n/a\n", scr);
	}

	for(int i = 0; i < MAXCHANNELS; i++) 
	{
		usedflags[i] = false;
		for(int j = 0; j < gpsdata->satellites_used; j++) 
		{
			if(gpsdata->used[j] == gpsdata->PRN[i]) 
			{
				usedflags[i] = true;
			}
		}
	}

	if(gpsdata->satellites_visible != 0) 
	{
		for(int l = 0; l < MAX_POSSIBLE_SATS; l++) 
		{
			if(l < gpsdata->satellites_visible) 
			{
				char used = ' ';
				if (usedflags[l]) 
				{
					used = 'Y';
				} 
				else 
				{
					used = 'N';
				}
				if (gpsdata->fix.mode <= MODE_2D) 
				{
					fprintf(stdout, "PRN: %3d Elevation: N/A Azimuth: %03d SNR: %02.0f Used: %c\n", gpsdata->PRN[l], gpsdata->azimuth[l], gpsdata->ss[l], used);
				}
				else 
				{
					fprintf(stdout, "PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02.0f Used: %c\n", gpsdata->PRN[l], gpsdata->elevation[l], gpsdata->azimuth[l], gpsdata->ss[l], used);						
				}					
			}
		}
	}
}