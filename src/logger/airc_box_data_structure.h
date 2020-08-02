#ifndef AIRC_BOX_DATA_STRUCTURE_H
#define AIRC_BOX_DATA_STRUCTURE_H

typedef struct dataPacket
{
    double temp;
    double humidity;
    double co2;
    double tvoc;
    double pressure;
    double co;
    double no2;
    double so2;
    double o3;
    double hcho;
    double pm2_5;
    double pm10;
}airc_box_dataPacket_S;

#endif