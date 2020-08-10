
#ifndef AIRC_BOX_DATA_PROCESSOR_H
#define AIRC_BOX_DATA_PROCESSOR_H

#include "airc_box_data_structure.h"

int airc_box_connect(int *airc_box_sock, const char *ip, struct sockaddr_in *airc_box_sockaddr);
int airc_box_get_info(int airc_box_sock, char buf[], int buf_size, int *offset, airc_box_dataPacket_S *data_recive);

#endif
