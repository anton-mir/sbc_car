#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "xlgyro_data_helper.h"
#include "console_helper.h"

static double rand_value(double min, double max) 
{
    srand(time(NULL));
    double modulo = RAND_MAX / (max - min);
    return min + (rand() / modulo);
}

static void fill_packet_data(XLGYRO_DATA_S *data, bool obstacle, XLGYRO_PACKET_PARAMETERS_S parameters)
{
    data->averaged.axisValue[E_X_AXIS] = rand_value(parameters.z_axis_min, parameters.z_axis_max);
    data->averaged.axisValue[E_Y_AXIS] = rand_value(parameters.z_axis_min, parameters.z_axis_max);
    data->averaged.axisValue[E_Z_AXIS] = rand_value(parameters.z_axis_min, parameters.z_axis_max);

    data->current.axisValue[E_X_AXIS] = rand_value(parameters.z_axis_min * 2, parameters.z_axis_max * 2);
    data->current.axisValue[E_Y_AXIS] = rand_value(parameters.z_axis_min * 2, parameters.z_axis_max * 2);

    if (obstacle) {
        if ((int)rand_value(0, 2) == 0) {
            data->current.axisValue[E_Z_AXIS] = rand_value(parameters.z_axis_min * 2, parameters.z_axis_min);
        }
        else {
            data->current.axisValue[E_Z_AXIS] = rand_value(parameters.z_axis_max, parameters.z_axis_max * 2);
        }
    }
    else {
        data->current.axisValue[E_Z_AXIS] = rand_value(parameters.z_axis_min, parameters.z_axis_max);
    }

    if (data->current.axisValue[E_X_AXIS] > data->averaged.axisValue[E_X_AXIS]) {
        data->max.axisValue[E_X_AXIS] = data->current.axisValue[E_X_AXIS];
        data->min.axisValue[E_X_AXIS] = data->averaged.axisValue[E_X_AXIS];
    }
    else {
        data->min.axisValue[E_X_AXIS] = data->current.axisValue[E_X_AXIS];
        data->max.axisValue[E_X_AXIS] = data->averaged.axisValue[E_X_AXIS];
    }

    if (data->current.axisValue[E_Y_AXIS] > data->averaged.axisValue[E_Y_AXIS]) {
        data->max.axisValue[E_Y_AXIS] = data->current.axisValue[E_Y_AXIS];
        data->min.axisValue[E_Y_AXIS] = data->averaged.axisValue[E_Y_AXIS];
    }
    else {
        data->min.axisValue[E_Y_AXIS] = data->current.axisValue[E_Y_AXIS];
        data->max.axisValue[E_Y_AXIS] = data->averaged.axisValue[E_Y_AXIS];
    }

    if (data->current.axisValue[E_Z_AXIS] > data->averaged.axisValue[E_Z_AXIS]) {
        data->max.axisValue[E_Z_AXIS] = data->current.axisValue[E_Z_AXIS];
        data->min.axisValue[E_Z_AXIS] = data->averaged.axisValue[E_Z_AXIS];
    }
    else {
        data->min.axisValue[E_Z_AXIS] = data->current.axisValue[E_Z_AXIS];
        data->max.axisValue[E_Z_AXIS] = data->averaged.axisValue[E_Z_AXIS];
    }
}

XLGYRO_PACKET_S generate_packet(XLGYRO_PACKET_PARAMETERS_S parameters)
{
    XLGYRO_PACKET_S packet = { 0 };
    XLGYRO_DATA_S data = { 0 };
    memset(&data, 0, sizeof(XLGYRO_DATA_S));

    bool obstacle = (int)rand_value(0, 2);

    fill_packet_data(&data, obstacle, parameters);
    
    packet.preambule1 = XLGYRO_PREAMBULE_VALUE;
    packet.preambule2 = XLGYRO_PREAMBULE_VALUE;
    memcpy(&packet.data, &data, sizeof(XLGYRO_DATA_S));
    packet.isObstacle = obstacle;

    for (int idx = 0; idx < XLGYRO_TRAILER_SIZE; ++idx)
    {
        packet.trailer[idx] = XLGYRO_TRAILER_VALUE;
    }

    #ifdef DEBUG_LOG
    char packet_str[512];
    sprintf(
        packet_str,
        "PACKET GENERATED:\n" //18
        "\tPREAMBULE1: %d\n" //24
        "\tPREAMBULE2: %d\n" //24
        "\tDATA:\n" //7
        "\t\tAVERAGED: X = %f Y = %f Z = %f\n" //87
        "\t\tCURRENT: X = %f Y = %f Z = %f\n" //76
        "\t\tMIN: X = %f Y = %f Z = %f\n" //82
        "\t\tMAX: X = %f Y = %f Z = %f\n" //82
        "\tOBSTACLE: %d\n", //22
        packet.preambule1, packet.preambule2, 
        packet.data.averaged.axisValue[E_X_AXIS], packet.data.averaged.axisValue[E_Y_AXIS], packet.data.averaged.axisValue[E_Z_AXIS],
        packet.data.current.axisValue[E_X_AXIS], packet.data.current.axisValue[E_Y_AXIS], packet.data.current.axisValue[E_Z_AXIS],
        packet.data.min.axisValue[E_X_AXIS], packet.data.min.axisValue[E_Y_AXIS], packet.data.min.axisValue[E_Z_AXIS],
        packet.data.max.axisValue[E_X_AXIS], packet.data.max.axisValue[E_Y_AXIS], packet.data.max.axisValue[E_Z_AXIS],
        packet.isObstacle
    );
    print_yellow(packet_str);
    #endif

    return packet;
}