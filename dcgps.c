#include "header.h"
#include "gps-utils.h"



int main(void)
{
	static struct fixsource_t source;
	static struct gps_data_t *gpsdata;
	gpsdata = malloc(sizeof(struct gps_data_t));
	memset(gpsdata, 0, (sizeof(struct gps_data_t)));
	bool usedflags[MAXCHANNELS];
	char scr[128];
	source.server = LOCAL_HOST;
	source.port = DEFAULT_GPSD_PORT;
	source.device = NULL;

	if(gps_open(source.server, source.port, gpsdata) == -1) {
		printf("gps not opened\n");
	} else {
		printf("gps opened\n");
	}
	
	
	gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

	readGpsData(gpsdata);

	free(gpsdata);
	return 0;
}
