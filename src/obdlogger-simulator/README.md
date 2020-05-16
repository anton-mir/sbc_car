**OBD Simulator**

Command line utility to simulate and send data on 127.0.0.1:11333 in format required for obdlogger "/src/sbc-car/src/logger".

To change parameters of simulation use **1. Change parameters:**, input **1** in menu.

Parameters for simulation:

- XLGYRO_TRAILER_SIZE, by default is (0x04);
- XLGYRO_TRAILER_VALUE, by default is (0xA5);
- XLGYRO_PREAMBULE_VALUE, by default is (0xAA55);
- DEFAULT_DEVIATION_HI, by default is (300). This is highest value of gyroscope;
- DEFAULT_DEVIATION_LO, by default is (-300). This is lowest value of gyroscope;
- Z_AXIS_THD_HI, by default is (0.4). This is high value to define pit;
- Z_AXIS_THD_LO, by default is (-0.4). This is low value to define pit;
- ROAD_QUALITY, by default is (3). This parameter set how many pits on road should generate (not using yet);

To start simulation use **2. Start simulation:**, input **2** in menu.

If simulation already started this step will ignore.

To exit program use **3. Exit:**, input **3** in menu.

**Build OBD Simulator**

Build will generate executable file in: `./bin/obdlogger-simulator`.

To build project run:
```bash
./build.sh
```

**Run OBD Simulator**

To run follow next commands:

Run **gpsfake**:
```bash
gpsfake -c 1 [YOUR_PATH_TO_REPOSITORY]/GL-SMARTCITY/sbc-platform/car_path_simulation.nmea
```

Run **obdgpslogger**:
```bash
cd [YOUR_PATH_TO_REPOSITORY]/GL-SMARTCITY/sbc-platform/build/src/sbc-car/bin && ./obdgpslogger
```

Run **obdlogger-simulator**:
```bash
./bin/obdlogger-simulator
```

Run **IC-lib**
```bash
cd [YOUR_PATH_TO_REPOSITORY]/GL-SMARTCITY/sbc-platform/build/src/IC-Lib && ./cluster-app conf/config.json
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
