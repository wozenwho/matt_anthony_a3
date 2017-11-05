#pragma once

#include <gps.h>

void readGpsData(struct gps_data_t *);
bool validateGPS(struct gps_data_t *);