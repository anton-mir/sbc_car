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
