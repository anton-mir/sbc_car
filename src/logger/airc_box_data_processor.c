#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "airc_box_data_processor.h"
#include "airc_box_data_structure.h"
#include <fcntl.h>

#define AIRC_BOX_PORT (11333)

int airc_box_connect(int *airc_box_sock, const char *ip, struct sockaddr_in *airc_box_sockaddr)
{
    if ((*airc_box_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nAirc_box: socket creation error\n");
        return -1;
    }

    airc_box_sockaddr->sin_family = AF_INET;
    airc_box_sockaddr->sin_port  = htons(AIRC_BOX_PORT);

    if(inet_pton(AF_INET, ip, &(airc_box_sockaddr->sin_addr)) <= 0)
    {
        printf("\nAirc_box: invalid address\n");
        return -2;
    }

    if(connect(*airc_box_sock, (struct sockaddr*)airc_box_sockaddr, sizeof(*airc_box_sockaddr)) < 0)
    {
        printf("\nAirc_box: connection failed\n");
        return -3;
    }

    return 0;
}

int airc_box_get_info(int airc_box_sock, char buf[], int buf_size, int *offset, airc_box_dataPacket_S *data_recive)
{
    int ret = 0, size = 0;
    char *curr = buf;
    static uint32_t AirC_Box_data_packets_counter = 0;

    // TODO: Make read() non-blocking and implement read timeout
    // in order to reconnect to AirC Box

    ret = read(airc_box_sock, (buf + *offset), buf_size);

    AirC_Box_data_packets_counter++;
    printf("airc_box: got packet number %d\n", AirC_Box_data_packets_counter);
    printf("airc_box: read %d bytes\n", ret);

    ret += *offset;
    printf("airc_box: %d bytes left to process\n", ret);

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
        // AirC Device info
        data_recive->device_id=((airc_box_dataPacket_S*)curr)->device_id;
        data_recive->device_working_status=((airc_box_dataPacket_S*)curr)->device_working_status;
        data_recive->device_message_counter=((airc_box_dataPacket_S*)curr)->device_message_counter;
        strncpy(data_recive->device_type, ((airc_box_dataPacket_S*)curr)->device_type, 19);
        strncpy(data_recive->device_description, ((airc_box_dataPacket_S*)curr)->device_description, 500);
        strncpy(data_recive->message_date_time, ((airc_box_dataPacket_S*)curr)->message_date_time, 24);
        data_recive->latitude=((airc_box_dataPacket_S*)curr)->latitude;
        data_recive->longitude=((airc_box_dataPacket_S*)curr)->longitude;
        data_recive->altitude=((airc_box_dataPacket_S*)curr)->altitude;
        // Sensors data
        data_recive->temp_internal=((airc_box_dataPacket_S*)curr)->temp_internal;
        data_recive->temp=((airc_box_dataPacket_S*)curr)->temp;
        data_recive->humidity=((airc_box_dataPacket_S*)curr)->humidity;
        data_recive->co2=((airc_box_dataPacket_S*)curr)->co2;
        data_recive->tvoc=((airc_box_dataPacket_S*)curr)->tvoc;
        data_recive->pressure=((airc_box_dataPacket_S*)curr)->pressure;
        data_recive->co=((airc_box_dataPacket_S*)curr)->co;
        data_recive->co_temp=((airc_box_dataPacket_S*)curr)->co_temp;
        data_recive->co_hum=((airc_box_dataPacket_S*)curr)->co_hum;
        data_recive->co_err=((airc_box_dataPacket_S*)curr)->co_err;
        data_recive->no2=((airc_box_dataPacket_S*)curr)->no2;
        data_recive->no2_temp=((airc_box_dataPacket_S*)curr)->no2_temp;
        data_recive->no2_hum=((airc_box_dataPacket_S*)curr)->no2_hum;
        data_recive->no2_err=((airc_box_dataPacket_S*)curr)->no2_err;
        data_recive->so2=((airc_box_dataPacket_S*)curr)->so2;
        data_recive->so2_temp=((airc_box_dataPacket_S*)curr)->so2_temp;
        data_recive->so2_hum=((airc_box_dataPacket_S*)curr)->so2_hum;
        data_recive->so2_err=((airc_box_dataPacket_S*)curr)->so2_err;
        data_recive->o3=((airc_box_dataPacket_S*)curr)->o3;
        data_recive->o3_temp=((airc_box_dataPacket_S*)curr)->o3_temp;
        data_recive->o3_hum=((airc_box_dataPacket_S*)curr)->o3_hum;
        data_recive->o3_err=((airc_box_dataPacket_S*)curr)->o3_err;
        data_recive->hcho=((airc_box_dataPacket_S*)curr)->hcho;
        data_recive->pm2_5=((airc_box_dataPacket_S*)curr)->pm2_5;
        data_recive->pm10=((airc_box_dataPacket_S*)curr)->pm10;
        curr += sizeof(airc_box_dataPacket_S);
        size -= sizeof(airc_box_dataPacket_S);
    }
    return ret;
}

