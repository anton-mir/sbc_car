#include "ccan_json.h"

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
    json_append_member(state, "gear", json_mkstring("1"));
    json_append_member(state, "laneId", json_mknumber(0.0));
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
    json_append_member(state, "gear", json_mkstring("1"));
    json_append_member(state, "laneId", json_mknumber(0.0));
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

char *generate_json_box(int id, char *skin_name, double lat, double lon,double temp, double humidity, double co2, double tvoc, double pressure, double co, double no2, double so2, double o3, double hcho, double pm2_5, double pm10)
{
    struct JsonNode *message = json_mkobject(), *state = json_mkobject();

    json_append_member(message, "id", json_mknumber(id));
    json_append_member(message, "skin", json_mkstring(skin_name));
    json_append_member(message, "name", json_mkstring("AirC Box"));
    json_append_member(message, "latitude", json_mknumber(lat));
    json_append_member(message, "longitude", json_mknumber(lon));
    json_append_member(message, "state", state);

    json_append_member(state, "temp", json_mknumber(temp));
    json_append_member(state, "humidity", json_mknumber(humidity));
    json_append_member(state, "pressure", json_mknumber(pressure));
    json_append_member(state, "co2", json_mknumber(co2));
    json_append_member(state, "tvoc", json_mknumber(tvoc));
    json_append_member(state, "co", json_mknumber(co));
    json_append_member(state, "no2", json_mknumber(no2));
    json_append_member(state, "so2", json_mknumber(so2));
    json_append_member(state, "o3", json_mknumber(o3));
    json_append_member(state, "hcho", json_mknumber(hcho));
    json_append_member(state, "pm2_5", json_mknumber(pm2_5));
    json_append_member(state, "pm10", json_mknumber(pm10));

    json_append_member(message, "type", json_mkstring("AirC_Box"));


    char *res = json_encode(message);
    json_delete(message);

    return res;
}
