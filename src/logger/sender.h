#include "airc_box_data_structure.h"

char *generate_json(int id,
        char *skin_name,
        double lat,
        double lon,
        int speed,
        double course,
        int rpm,
        int pit);

char *generate_json_car(int id,
			char *skin_name,
 			double lat,
			double lon,
			int speed,
			double course,
			int rpm,
			int pit,
			double temp,
			double humidity,
			double co2,
			double tvoc);

char *generate_json_box(airc_box_dataPacket_S *data_recive, double lat, double lon);
