#include "header.h"
#include "gpsprint.h"


/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION: 	printGpsData
--
--  DATE:		November 3, 2017
--
--  REVISIONS:		
--
--  DESIGNER:		
--
--  PROGRAMMER:		
--
--  INTERFACE:		void printGpsData(struct gps_data_t * gpsdata)
--						struct gps_data_t * gpsdata: The location and satellite info that was returned from the GPS dongle
--
--
--  RETURNS:		void.
--
--  NOTES:
--  This function is called when a gpsdata structure needs their info to be printed to the screen 
----------------------------------------------------------------------------------------------------------------------*/
void printGpsData(struct gps_data_t * gpsdata) {

	bool usedflags[MAXCHANNELS];
	char scr[128];

	
	if (gpsdata->fix.mode >= MODE_2D && isnan (gpsdata->fix.latitude) == 0)
	{


		printf("----------------------------------\n");
		(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
		fprintf(stdout, "\n%s ", scr);
		
		fprintf (stdout, "Latitude: %.6f %c; ", (gpsdata->fix.latitude < 0) ? gpsdata->fix.latitude * -1 : gpsdata->fix.latitude, (gpsdata->fix.latitude < 0) ? 'S' : 'N');

		fprintf (stdout, "longitude: %.6f %c; \n\n", (gpsdata->fix.longitude < 0) ? gpsdata->fix.longitude * -1 : gpsdata->fix.longitude, (gpsdata->fix.longitude < 0) ? 'W' : 'E');
		
		fflush (stdout);
	} 
	else 
	{
		(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
		fprintf(stdout, "\n%s  n/a  n/a\n", scr);
	}



	for(int i = 0; i < MAXCHANNELS; i++) {

			usedflags[i] = false;
			for(int j = 0; j < gpsdata->satellites_used; j++) {
				
				if(gpsdata->used[j] == gpsdata->PRN[i]) {
					usedflags[i] = true;
				}
			}
		}

		if(gpsdata->satellites_visible != 0) {
			for(int l = 0; l < MAX_POSSIBLE_SATS; l++) {
				if(l < gpsdata->satellites_visible) {

					char used = ' ';
					if (usedflags[l]) {
						used = 'Y';
					} else {
						used = 'N';
					}

					if (gpsdata->fix.mode <= MODE_2D) {
						fprintf(stdout, "PRN: %3d Elevation: N/A Azimuth: %03d SNR: %02.0f Used: %c\n", gpsdata->PRN[l], gpsdata->azimuth[l], gpsdata->ss[l], used);
					} else {
						fprintf(stdout, "PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02.0f Used: %c\n", gpsdata->PRN[l], gpsdata->elevation[l], gpsdata->azimuth[l], gpsdata->ss[l], used);						
					}
					
					
				}
			}
		}
		


	
}