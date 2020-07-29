/* Copyright 2009 Gary Briggs

This file is part of obdgpslogger.

obdgpslogger is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

obdgpslogger is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with obdgpslogger.  If not, see <http://www.gnu.org/licenses/>.
*/


/** \file
 \brief gps communications
 */

#ifdef HAVE_GPSD

#include <gps.h>
static struct gps_data_t my_gps_data;

struct gps_data_t *opengps(char *server, char *port) {
	int result;

	result = gps_open(server, port, &my_gps_data);
	if (result < 0)
		return NULL;

	result = gps_stream(&my_gps_data, WATCH_ENABLE|WATCH_NEWSTYLE, NULL);
	if (result < 0)
		return NULL;

	return &my_gps_data;
}

void closegps(struct gps_data_t *g) {
	gps_close(g);
}

int getgpsposition(struct gps_data_t *g, double *lat, double *lon, double *alt, double *speed, double *course, double *gpstime) {
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(g->gps_fd, &fds);
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;

	int timesround = 0;
	int count;
	do {
		timesround++;
		count = select(g->gps_fd + 1, &fds, NULL, NULL, &timeout);
		if(count > 0) {
#ifdef HAVE_GPSD_V3
			gps_read(g, NULL, 0);
//#else
			gps_send(g, "o");
#endif //HAVE_GPSD_V3
		}
	} while (count > 0);

	// if(timesround > 1) {
	//	printf("Times around gpsd loop: %i\n", timesround);
	// }

	if(g->fix.mode < MODE_2D) {
		return -1;
	}
	if(g->fix.mode == MODE_2D) {
		*lat = g->fix.latitude;
		*lon = g->fix.longitude;
		*course = g->fix.track;
		*speed = g->fix.speed;
		*gpstime = g->fix.time.tv_sec;
		return 0;
	}
	if(g->fix.mode == MODE_3D) {
		*lat = g->fix.latitude;
		*lon = g->fix.longitude;
		*alt = g->fix.altitude;
		*course = g->fix.track;
		*speed = g->fix.speed;
		*gpstime = g->fix.time.tv_sec;
		return 1;
	}
	// Shouldn't be able to get to here...
	return -1;
}

#endif //HAVE_GPSD

