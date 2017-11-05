#pragma once


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

