#include "header.h"
#include "gps-utils.h"
#include "gpsprint.h"



void readGpsData(struct gps_data_t * gpsdata) {

	while(1) {
		if(!gps_waiting(gpsdata, 5000000)) {
			printf("timed out\n");
		} else {
			if(!validateGPS(gpsdata)) {
				return;
			} else {
				
				if (gpsdata->set) {

					printGpsData(gpsdata);
				} else {
					printf("gps_set failed");
				}
				
			}
		}
	}
}



bool validateGPS(struct gps_data_t * gpsdata) {
	if(gps_read(gpsdata) == -1) {
		printf("gps_read failed\n");
		return false;
	} 
	return true;
}





