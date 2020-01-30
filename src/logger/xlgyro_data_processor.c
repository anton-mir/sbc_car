
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "xlgyro_data_processor.h"

#define XLGYRO_PORT (11333)


int xlgyro_connect(int *xlgyro_sock, struct sockaddr_in *xlgyro_sockaddr) {
    if ((*xlgyro_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("xlgyro: socket creation error\n");
		return -1;
	}
	
	xlgyro_sockaddr->sin_family = AF_INET;
	xlgyro_sockaddr->sin_port  = htons(XLGYRO_PORT);
	
	if(inet_pton(AF_INET, "127.0.0.1", &(xlgyro_sockaddr->sin_addr)) <= 0) {
		printf("xlgyro: invalid address\n");
		return -2;
	}
	
	if(connect(*xlgyro_sock, (struct sockaddr*)xlgyro_sockaddr, sizeof(*xlgyro_sockaddr)) < 0) {
		printf("xlgyro: connection failed\n");
		return -3;
	}
	
	return 0;
}

int xlgyro_get_info(int xlgyro_sock, char buf[], int buf_size, int *offset, int *obstacle) {
	int ret = 0, size = 0;
	char *curr = buf;

	
	ret = read(xlgyro_sock, (buf + *offset), buf_size);
	printf("xlgyro: read %d bytes\n", ret);
	ret += *offset;
	printf("xlgyro: %d bytes to process\n", ret);
	
	*offset = 0;
	*obstacle = 0;
	size = ret;
	while(size > 0) {
		if(size < sizeof(XLGYRO_PACKET_S)) {
			memcpy(buf, curr, size);
			*offset = size;
			break;
		}
		if(((XLGYRO_PACKET_S*)curr)->isObstacle)
			*obstacle = 1;
		curr += sizeof(XLGYRO_PACKET_S);
		size -= sizeof(XLGYRO_PACKET_S);
	}
	
	return ret;
}
