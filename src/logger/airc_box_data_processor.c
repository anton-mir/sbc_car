#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "airc_box_data_processor.h"
#include "airc_box_data_structure.h"

#define AIRC_BOX_PORT (11333)
#define AIRC_BOX_DHCP "192.168.0.103"

int airc_box_connect(int *airc_box_sock, struct sockaddr_in *airc_box_sockaddr)
{
    if ((*airc_box_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("airc_box: socket creation error\n");
        return -1;
    }

    airc_box_sockaddr->sin_family = AF_INET;
    airc_box_sockaddr->sin_port  = htons(AIRC_BOX_PORT);

    if(inet_pton(AF_INET, AIRC_BOX_DHCP, &(airc_box_sockaddr->sin_addr)) <= 0)
    {
        printf("airc_box: invalid address\n");
        return -2;
    }

    if(connect(*airc_box_sock, (struct sockaddr*)airc_box_sockaddr, sizeof(*airc_box_sockaddr)) < 0)
    {
        printf("airc_box: connection failed\n");
        return -3;
    }

    return 0;
}

int airc_box_get_info(int airc_box_sock, char buf[], int buf_size, int *offset, airc_box_dataPacket_S *data_recive)
{
    int ret = 0, size = 0;
    char *curr = buf;
    ret = read(airc_box_sock, (buf + *offset), buf_size);
    printf("airc_box: read %d bytes\n", ret);
    ret += *offset;
    printf("airc_box: %d bytes to process\n", ret);

    *offset = 0;
    size = ret;
    while(size > 0)
    {
        if(size < sizeof(airc_box_dataPacket_S))
        {
            memcpy(buf, curr, size);
            *offset = size;
            break;
        }
        data_recive->temp=((airc_box_dataPacket_S*)curr)->temp;
        data_recive->humidity=((airc_box_dataPacket_S*)curr)->humidity;
        data_recive->co2=((airc_box_dataPacket_S*)curr)->co2;
        data_recive->tvoc=((airc_box_dataPacket_S*)curr)->tvoc;
        data_recive->pressure=((airc_box_dataPacket_S*)curr)->pressure;
        data_recive->co=((airc_box_dataPacket_S*)curr)->co;
        data_recive->no2=((airc_box_dataPacket_S*)curr)->no2;
        data_recive->so2=((airc_box_dataPacket_S*)curr)->so2;
        data_recive->o3=((airc_box_dataPacket_S*)curr)->o3;
        data_recive->hcho=((airc_box_dataPacket_S*)curr)->hcho;
        data_recive->pm2_5=((airc_box_dataPacket_S*)curr)->pm2_5;
        data_recive->pm10=((airc_box_dataPacket_S*)curr)->pm10;
        curr += sizeof(airc_box_dataPacket_S);
        size -= sizeof(airc_box_dataPacket_S);
    }
    return ret;
}

