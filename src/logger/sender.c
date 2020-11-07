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

char *generate_json_box(int id, char *skin_name, double lat, double lon, airc_box_dataPacket_S *data_recive)
{
    struct JsonNode *message = json_mkobject(), *state = json_mkobject();

    json_append_member(message, "id", json_mknumber(id));
    json_append_member(message, "skin", json_mkstring(skin_name));
    json_append_member(message, "name", json_mkstring("AirC Box"));
    json_append_member(message, "latitude", json_mknumber(lat));
    json_append_member(message, "longitude", json_mknumber(lon));
    json_append_member(message, "state", state);

    json_append_member(state, "temp", json_mknumber(data_recive->temp));
    json_append_member(state, "humidity", json_mknumber(data_recive->humidity));
    json_append_member(state, "pressure", json_mknumber(data_recive->pressure));
    json_append_member(state, "co2", json_mknumber(data_recive->co2));
    json_append_member(state, "tvoc", json_mknumber(data_recive->tvoc));
    json_append_member(state, "co", json_mknumber(data_recive->co));
    json_append_member(state, "co_temp", json_mknumber(data_recive->co_temp));
    json_append_member(state, "co_hum", json_mknumber(data_recive->co_hum));
    json_append_member(state, "no2", json_mknumber(data_recive->no2));
    json_append_member(state, "no2_temp", json_mknumber(data_recive->no2_temp));
    json_append_member(state, "no2_hum", json_mknumber(data_recive->no2_hum));
    json_append_member(state, "so2", json_mknumber(data_recive->so2));
    json_append_member(state, "so2_temp", json_mknumber(data_recive->so2_temp));
    json_append_member(state, "so2_hum", json_mknumber(data_recive->so2_hum));
    json_append_member(state, "o3", json_mknumber(data_recive->o3));
    json_append_member(state, "o3_temp", json_mknumber(data_recive->o3_temp));
    json_append_member(state, "o3_hum", json_mknumber(data_recive->o3_hum));
    json_append_member(state, "hcho", json_mknumber(data_recive->hcho));
    json_append_member(state, "pm2_5", json_mknumber(data_recive->pm2_5));
    json_append_member(state, "pm10", json_mknumber(data_recive->pm10));

    json_append_member(message, "type", json_mkstring("AirC_Box"));


    char *res = json_encode(message);
    json_delete(message);

    return res;
}
