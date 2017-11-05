#include "header.h"
#include "gpsprint.h"


void printGpsData(gps_data_t * gpsdata) {

	printf("gps_set passed\n");
	for(int i = 0; i < MAXCHANNELS; i++) {

		usedflags[i] = false;
		for(int j = 0; j < gpsdata->satellites_used; j++) {
			printf("found satellites\n");
			if(gpsdata->skyview[i].used) {
				usedflags[i] = true;
			}
		}
		if(gpsdata->satellites_visible != 0) {
			for(int l = 0; l < MAX_POSSIBLE_SATS; l++) {
				if(l < gpsdata->satellites_visible) {
					printf("printing satellite info\n");
					//fprintf(stdout, "%3d\t%3d\t%3d\t%3d\t%c\n", gpsdata->skyview[l].PRN, gpsdata->skyview[l].elevation, gpsdata->skyview[l].azimuth, gpsdata->skyview[l].ss, usedflags[l] ? 'Y':'N');
				}
			}
		}
	}
}