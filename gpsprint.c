#include "header.h"
#include "gpsprint.h"


void printGpsData(struct gps_data_t * gpsdata) {

	bool usedflags[MAXCHANNELS];
	char scr[128];

	(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
	fprintf(stdout, "%s ", scr);
	if (gpsdata->fix.mode >= MODE_2D && isnan (gpsdata->fix.latitude) == 0)
	{
		/*
		fprintf (stdout, "Latitude: %s %c; ", deg_to_str(deg_type, fabs (gpsdata->fix.latitude)),
		(gpsdata->fix.latitude < 0) ? 'S' : 'N');

		fprintf (stdout, "Latitude: %s %c; \n\n", deg_to_str(deg_type, fabs (gpsdata->fix.longitude)),
		(gpsdata->fix.longitude < 0) ? 'E' : 'W');
*/
		fprintf(stdout, "%d   %d\n", gpsdata->fix.latitude , gpsdata->fix.longitude );
		fflush (stdout);

		for(int i = 0; i < MAXCHANNELS; i++) {

			usedflags[i] = false;
			for(int j = 0; j < gpsdata->satellites_used; j++) {
				if(gpsdata->skyview[i].used) {
					usedflags[i] = true;
				}
			}
			if(gpsdata->satellites_visible != 0) {
				for(int l = 0; l < MAX_POSSIBLE_SATS; l++) {
					if(l < gpsdata->satellites_visible) {
						/*
						if (gpsdata->fix.mode == MODE_2D) {
							fprintf(stdout, "PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02d Used: %c\n", gpsdata->skyview[l].PRN, gpsdata->skyview[l].elevation, gpsdata->skyview[l].azimuth, gpsdata->skyview[l].ss, usedflags[l] ? 'Y':'N');

						} else {
							fprintf(stdout, "PRN: %3d Elevation: N/A Azimuth: %03d SNR: %02d Used: %c\n", gpsdata->skyview[l].PRN, gpsdata->skyview[l].azimuth, gpsdata->skyview[l].ss, usedflags[l] ? 'Y':'N');

						}
						*/
						if (gpsdata->fix.mode == MODE_2D) {
							fprintf(stdout, "PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02d Used: %c\n", gpsdata->PRN[l], gpsdata->elevation[l], gpsdata->azimuth[l], gpsdata->ss[l], usedflags[l] ? 'Y':'N');

						} else {
							fprintf(stdout, "PRN: %3d Elevation: N/A Azimuth: %03d SNR: %02d Used: %c\n", gpsdata->PRN[l], gpsdata->elevation[l], gpsdata->azimuth[l], gpsdata->ss[l], usedflags[l] ? 'Y':'N');
						}

						
					}
				}
			}
		}
	}
	else
		printf("n/a\n");


	
}