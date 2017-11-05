#include "header.h"
#include "gps-utils.h"
#include "gpsprint.h"



void readGpsData(struct gps_data_t * gpsdata) {

	while(1) {
		if(!gps_waiting(gpsdata, 5000000)) {
			printf("timed out\n");
		} else {
			if(gps_read(gpsdata) == -1) {
				printf("gps_read failed\n");
			} else {
				//(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
				//fprintf(stdout, "%s\t%d\t%d\t\n\n", scr, gpsdata->fix.latitude, gpsdata->fix.longitude);
				if (gpsdata->set) {

					printGpsData(gpsdata);
				} else {
					printf("gps_set failed");
				}
				
			}
		}
	}
}