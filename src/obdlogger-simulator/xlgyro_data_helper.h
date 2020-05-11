#ifndef XLGYRO_DATA_HELPER_H
#define XLGYRO_DATA_HELPER_H

#include <stdint.h>
#include <stdbool.h>

#define XLGYRO_TRAILER_SIZE                 (4)
#define XLGYRO_TRAILER_VALUE                (0xA5)
#define XLGYRO_PREAMBULE_VALUE              (0xAA55)

#define DEFAULT_DEVIATION_HI    (double)(300.0)
#define DEFAULT_DEVIATION_LO    (double)(-300.0)
#define Z_AXIS_THD_HI           (double)(0.4)
#define Z_AXIS_THD_LO           (double)(-0.4)

typedef enum
{
    VERY_BAD = 1,
    BAD,
    NORMAL,
    GOOD,
    PERFECT
} ROAD_QUALITY;

typedef enum
{
    E_X_AXIS = 0,
    E_Y_AXIS,
    E_Z_AXIS,
    E_AXIS_COUNT
} AXISES;

typedef struct XLGYRO_PACKET_PARAMETERS_STRUCT
{
    ROAD_QUALITY quality;
    int trailer_size;
    int trailer_value;
    int preambule_value;
    double deviation_min;
    double deviation_max;
    double z_axis_min;
    double z_axis_max;
} XLGYRO_PACKET_PARAMETERS_S;

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

XLGYRO_PACKET_S generate_packet(XLGYRO_PACKET_PARAMETERS_S parameters);

#endif