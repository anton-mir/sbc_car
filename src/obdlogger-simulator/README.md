**OBD Simulator**

Command line utility to simulate and send data on 127.0.0.1:11333 in format required for obdlogger "/src/sbc-car/src/logger".

**Build OBD Simulator**

Build will generate executable file in: `./bin/obdlogger-simulator`.

To build project run:
```bash
./build.sh
```

**ODB Logger gyroscope data format to send**:
```c
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
```
