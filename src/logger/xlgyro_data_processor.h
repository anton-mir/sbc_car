#ifndef XLGYRO_DATA_PROCESSOR_H
#define XLGYRO_DATA_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

#define XLGYRO_TRAILER_SIZE                 (4)
#define XLGYRO_TRAILER_VALUE                (0xA5)
#define XLGYRO_PREAMBULE_VALUE              (0xAA55)

typedef enum
{
    E_X_AXIS = 0,
    E_Y_AXIS,
    E_Z_AXIS,
    E_AXIS_COUNT
} AXISES;

typedef struct AXIS_DOUBLE_VALUE_STRUCT
{
    double axisValue[E_AXIS_COUNT];
} AXIS_DOUBLE_VALUE_S;

typedef struct XLGYRO_DATA_STRUCT
{
    AXIS_DOUBLE_VALUE_S current;
    AXIS_DOUBLE_VALUE_S min;
    AXIS_DOUBLE_VALUE_S max;
    AXIS_DOUBLE_VALUE_S averaged;
} XLGYRO_DATA_S;

typedef struct XLGYRO_PACKET_STRUCT
{
    uint16_t preambule1;
    uint16_t preambule2;
    XLGYRO_DATA_S data;
    bool isObstacle;
    uint8_t trailer[XLGYRO_TRAILER_SIZE];
} XLGYRO_PACKET_S;

int xlgyro_connect(int *xlgyro_sock, struct sockaddr_in *xlgyro_sockaddr);
int xlgyro_get_info(int xlgyro_sock, char buf[], int buf_size, int *offset, int *obstacle);

#endif /* XLGYRO_DATA_PROCESSOR_H */
