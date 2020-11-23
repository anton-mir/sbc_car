#include "ccan_json.h"
#include "airc_box_data_structure.h"

char *generate_json(int id, char *skin_name, double lat, double lon, int speed, double course, int rpm, int pit)
{
    struct JsonNode *message = json_mkobject(), *state = json_mkobject();

    json_append_member(message, "id", json_mknumber(id));
    json_append_member(message, "skin", json_mkstring(skin_name));
    json_append_member(message, "name", json_mkstring("RPi Car"));
    json_append_member(message, "state", state);

    json_append_member(state, "acceleration", json_mknumber(0.0));
    json_append_member(state, "course", json_mknumber(course));
    json_append_member(state, "latitude", json_mknumber(lat));
    json_append_member(state, "longitude", json_mknumber(lon));
    json_append_member(state, "speed", json_mknumber(speed));
    json_append_member(state, "rpm", json_mknumber(rpm));
    json_append_member(state, "special", json_mkbool(0));
    json_append_member(state, "gear", json_mknumber(1));
    json_append_member(state, "laneid", json_mknumber(0.0));
    json_append_member(state, "pit", json_mknumber(pit));

    json_append_member(message, "status", json_mkstring("Moving"));
    json_append_member(message, "type", json_mkstring("Car"));

    char *res = json_encode(message);
    json_delete(message);

    return res;
}

char *generate_json_car(int id, char *skin_name, double lat, double lon, int speed, double course, int rpm, int pit, double temp, double humidity, double co2, double tvoc)
{
    struct JsonNode *message = json_mkobject(), *state = json_mkobject();

    json_append_member(message, "id", json_mknumber(id));
    json_append_member(message, "skin", json_mkstring(skin_name));
    json_append_member(message, "name", json_mkstring("RPi Car"));
    json_append_member(message, "state", state);

    json_append_member(state, "acceleration", json_mknumber(0.0));
    json_append_member(state, "course", json_mknumber(course));
    json_append_member(state, "latitude", json_mknumber(lat));
    json_append_member(state, "longitude", json_mknumber(lon));
    json_append_member(state, "speed", json_mknumber(speed));
    json_append_member(state, "rpm", json_mknumber(rpm));
    json_append_member(state, "special", json_mkbool(0));
    json_append_member(state, "gear", json_mknumber(1));
    json_append_member(state, "laneid", json_mknumber(0.0));
    json_append_member(state, "pit", json_mknumber(pit));

    json_append_member(state, "temp", json_mknumber(temp));
    json_append_member(state, "humidity", json_mknumber(humidity));
    json_append_member(state, "co2", json_mknumber(co2));
    json_append_member(state, "tvoc", json_mknumber(tvoc));

    json_append_member(message, "status", json_mkstring("Moving"));
    json_append_member(message, "type", json_mkstring("AirC_Car"));

    char *res = json_encode(message);
    json_delete(message);

    return res;
}

char *generate_json_box(airc_box_dataPacket_S *data_recive)
{
    struct JsonNode *message = json_mkobject(), *sensors_data = json_mkobject(), *airc_device_data = json_mkobject();
    // AirC device info
    json_append_member(message, "id", json_mknumber(data_recive->device_id));
    json_append_member(message, "type", json_mkstring(data_recive->device_type));
    json_append_member(message, "skin", json_mkstring("AirC_box"));

    // AirC device info
    json_append_member(message, "airc_device_data", airc_device_data);
    json_append_member(airc_device_data, "id", json_mknumber(data_recive->device_id));
    json_append_member(airc_device_data, "status", json_mknumber(data_recive->device_working_status));
    json_append_member(airc_device_data, "message_counter", json_mknumber(data_recive->device_message_counter));
    json_append_member(airc_device_data, "type", json_mkstring(data_recive->device_type));
    json_append_member(airc_device_data, "description", json_mkstring(data_recive->device_description));
    json_append_member(airc_device_data, "date_time", json_mkstring(data_recive->message_date_time));
    json_append_member(airc_device_data, "latitude", json_mknumber(data_recive->latitude));
    json_append_member(airc_device_data, "longitude", json_mknumber(data_recive->longitude));
    json_append_member(airc_device_data, "altitude", json_mknumber(data_recive->altitude));

    // Sensors data
    json_append_member(message, "state", sensors_data);
    json_append_member(sensors_data, "temp_internal", json_mknumber(data_recive->temp_internal));
    json_append_member(sensors_data, "temp", json_mknumber(data_recive->temp));
    json_append_member(sensors_data, "humidity", json_mknumber(data_recive->humidity));
    json_append_member(sensors_data, "pressure", json_mknumber(data_recive->pressure));
    json_append_member(sensors_data, "co2", json_mknumber(data_recive->co2));
    json_append_member(sensors_data, "tvoc", json_mknumber(data_recive->tvoc));
    json_append_member(sensors_data, "co", json_mknumber(data_recive->co));
    json_append_member(sensors_data, "co_temp", json_mknumber(data_recive->co_temp));
    json_append_member(sensors_data, "co_hum", json_mknumber(data_recive->co_hum));
    json_append_member(sensors_data, "no2", json_mknumber(data_recive->no2));
    json_append_member(sensors_data, "no2_temp", json_mknumber(data_recive->no2_temp));
    json_append_member(sensors_data, "no2_hum", json_mknumber(data_recive->no2_hum));
    json_append_member(sensors_data, "so2", json_mknumber(data_recive->so2));
    json_append_member(sensors_data, "so2_temp", json_mknumber(data_recive->so2_temp));
    json_append_member(sensors_data, "so2_hum", json_mknumber(data_recive->so2_hum));
    json_append_member(sensors_data, "o3", json_mknumber(data_recive->o3));
    json_append_member(sensors_data, "o3_temp", json_mknumber(data_recive->o3_temp));
    json_append_member(sensors_data, "o3_hum", json_mknumber(data_recive->o3_hum));
    json_append_member(sensors_data, "hcho", json_mknumber(data_recive->hcho));
    json_append_member(sensors_data, "pm2_5", json_mknumber(data_recive->pm2_5));
    json_append_member(sensors_data, "pm10", json_mknumber(data_recive->pm10));

    char *res = json_encode(message);
    json_delete(message);

    return res;
}
