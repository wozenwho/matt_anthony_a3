#include "header.h"
#include "gpsprint.h"


void printGpsData(struct gps_data_t * gpsdata) {

	bool usedflags[MAXCHANNELS];
	char scr[128];

	//(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
	//fprintf(stdout, "%s\t%d\t%d\t\n\n", scr, gpsdata->fix.latitude, gpsdata->fix.longitude);

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
					//fprintf(stdout, "%3d\t%3d\t%3d\t%3d\t%c\n", gpsdata->skyview[l].PRN, gpsdata->skyview[l].elevation, gpsdata->skyview[l].azimuth, gpsdata->skyview[l].ss, usedflags[l] ? 'Y':'N');
				}
			}
		}
	}
}