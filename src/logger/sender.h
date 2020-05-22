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
char *generate_json_box(int id,
			char *skin_name,
			double lat,
			double lon,
			double temp,
			double humidity,
			double co2,
			double tvoc,
			double pressure,
			double co,
			double no2,
			double so2,
			double o3,
			double hcho,
			double pm2_5,
			double pm10);
