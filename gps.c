/*
 * gps.c
 * 
 * Copyright 2017 root <root@datacomm>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * d
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <gps.h>
#include <stdlib.h>
#include <string.h>
#define MAX_POSSIBLE_SATS	(MAXCHANNELS - 2)
#define LOCAL_HOST "127.0.0.1"
struct fixsource_t
{
	char *spec;
	char *server;
	char *port;
	char *device;
};

int main(void)
{
	static struct fixsource_t source;
	static struct gps_data_t *gpsdata;
	gpsdata = malloc(sizeof(struct gps_data_t));
	memset(gpsdata, 0, (sizeof(struct gps_data_t)));
	unsigned int flags = WATCH_ENABLE;
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
	
	while(1) {
		if(!gps_waiting(gpsdata, 5000000)) {
			printf("timed out\n");
		} else {
			if(gps_read(gpsdata) == -1 || gps_read(gpsdata) == 0) {
				printf("gps_read failed\n");
			} else {
				//(void)unix_to_iso8601(gpsdata->fix.time, scr, sizeof(scr));
				//fprintf(stdout, "%s\t%d\t%d\t\n\n", scr, gpsdata->fix.latitude, gpsdata->fix.longitude);
				for(int i = 0; i < MAXCHANNELS; i++) {

					usedflags[i] = false;
					for(int j = 0; j < gpsdata->satellites_used; j++) {
						printf("found satellites\n");
						if(gpsdata->used[i]) {
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
		}
	}
	free(gpsdata);
	return 0;
}

