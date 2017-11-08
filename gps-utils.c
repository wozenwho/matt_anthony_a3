#include "header.h"
#include "gps-utils.h"
#include "gpsprint.h"


/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:	readGpsData
--
--  DATE:		November 2, 2017
--
--  REVISIONS:		none
--
--  DESIGNER:		Anthony Vu
--
--  PROGRAMMER:		Anthony Vu
--
--  INTERFACE:		void readGpsData(struct gps_data_t * gpsdata)
--						struct gps_data_t * gpsdata: The location and satellite info that was returned from the GPS dongle
--
--  RETURNS:		void
--						
--
--  NOTES:
--  This function will continuously listen to the gps dongle for data and check the recieved data for error detection. Upon 
--  successful return from error detection the function will call a print function to print the gps info to the screen otherwise
--  upon unsuccesful error detection the program will teminate
----------------------------------------------------------------------------------------------------------------------*/
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



/*------------------------------------------------------------------------------------------------------------------
--  FUNCTION:	validateGPS
--
--  DATE:		November 2, 2017
--
--  REVISIONS:  
--
--  DESIGNER:		Anthony Vu
--
--  PROGRAMMER:		Anthony Vu
--
--  INTERFACE:		bool validateGPS(struct gps_data_t * gpsdata)
--						struct gps_data_t * gpsdata: The location and satellite info that was returned from the GPS dongle
--
--  RETURNS:		Returns a boolean value describing success or failure of the function 
--							true: the gpsdata contains valid data
--							false: the gpsdara contains invalid data
--						
--  NOTES:
--  This function is determines whether the gpsdata structure contains valid data and the gps dongle is recieving proper readings 
----------------------------------------------------------------------------------------------------------------------*/
bool validateGPS(struct gps_data_t * gpsdata) {
	int error;
	if((error = gps_read(gpsdata)) == -1) {
		printf("gps_read failed.\nCode: %d\nError: %s\nterminating stream\n", error, gps_errstr(error));
		return false;
	}
	return true;
}





