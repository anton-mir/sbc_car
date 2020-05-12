#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "console_helper.h"
#include "xlgyro_data_helper.h"
#include "xlgyro_data_simulator.h"
#include "server.h"

static bool simulation_running = false;

static int menu()
{
    int variant;
    printf("\n1. Change parameters: \n");
    printf("2. Start simulation: \n");
    printf("3. Exit: \n");
	printf("\nINPUT: ");
    scanf("%d", &variant);

    //data entry verification
    while (variant < 1 || variant > 3)
    {
        printf("\nIncorect input. Try again: ");
        scanf("%d", &variant);
    }
    return variant;
}

static void menu_change(XLGYRO_PACKET_PARAMETERS_S *parameters)
{
    int variant_change;

    clear_all();
    print_blue("***CHANGE INPUT PARAMETERS***\n");
    printf("1. XLGYRO_TRAILER_SIZE\n");
    printf("2. XLGYRO_TRAILER_VALUE\n");
    printf("3. XLGYRO_PREAMBULE_VALUE\n");
    printf("4. DEFAULT_DEVIATION_HI\n");
    printf("5. DEFAULT_DEVIATION_LO\n");
    printf("6. Z_AXIS_THD_HI\n");
    printf("7. Z_AXIS_THD_LO\n");
    printf("8. ROAD_QUALITY\n");
	printf("\nINPUT: ");
    scanf("%d", &variant_change);

    //data entry verification
    while (variant_change < 1 || variant_change > 8)
    {
        printf("\nIncorect input. Try again: ");
        scanf("%d", &variant_change);
    }

    clear_all();

    switch (variant_change) {
		case 1:
			printf("XLGYRO_TRAILER_SIZE: ");
			scanf("%d", &parameters->trailer_size);
			break;
		case 2:
			printf("XLGYRO_TRAILER_VALUE: ");
			scanf("%d", &parameters->trailer_value);
			break;
		case 3:
			printf("XLGYRO_PREAMBULE_VALUE: ");
			scanf("%d", &parameters->preambule_value);
			break;
		case 4:
			printf("DEFAULT_DEVIATION_HI: ");
			scanf("%lf", &parameters->deviation_max);
			break;
		case 5:
			printf("DEFAULT_DEVIATION_LO: ");
			scanf("%lf", &parameters->deviation_min);
			break;
		case 6:
			printf("Z_AXIS_THD_HI: ");
			scanf("%lf", &parameters->z_axis_max);
			break;
		case 7:
			printf("Z_AXIS_THD_LO: ");
			scanf("%lf", &parameters->z_axis_min);
			break;
		case 8:
			printf("ROAD_QUALITY (1-5): ");
			scanf("%d", (int*)&parameters->quality);

			//data entry verification
			while (parameters->quality < 1 || parameters->quality > 5)
			{
				printf("\nIncorect input. Write (1-5):");
				scanf("%d", (int*)&parameters->quality);
			}
			break;
    }
}

static void start_simulation(XLGYRO_PACKET_PARAMETERS_S *parameters)
{
    if (create_server() < 0) 
	{
		#ifdef DEBUG_LOG
		print_red("Server start failed!");
		#endif
	}
	else 
	{
		#ifdef DEBUG_LOG
		print_green("Server start successed!");
		#endif
		simulation_running = true;
	}

	if (create_simulator(parameters) < 0) 
	{
		#ifdef DEBUG_LOG
		print_red("Simulator start failed!");
		#endif
	}
	else 
	{
		#ifdef DEBUG_LOG
		print_green("Simulator start successed!");
		#endif
		simulation_running &= true;
	}
}
static void stop_simulation()
{
	if (close_server() < 0)
	{
		#ifdef DEBUG_LOG
		print_red("Server stop failed!");
		#endif
	}
	else
	{
		simulation_running = false;
	}
	
	if (close_simulator() < 0)
	{
		#ifdef DEBUG_LOG
		print_red("Simulator stop failed!");
		#endif
	}
	else
	{
		simulation_running &= false;
	}
	
}

int main(int argc, char *argv[])
{
	CONSOLE_SIZE_S size = size_of_console();
	
	XLGYRO_PACKET_PARAMETERS_S parameters = { 0 };
	parameters.quality = NORMAL;
	parameters.trailer_size = XLGYRO_TRAILER_SIZE;
	parameters.trailer_value = XLGYRO_TRAILER_VALUE;
	parameters.preambule_value = XLGYRO_PREAMBULE_VALUE;
	parameters.deviation_max = DEFAULT_DEVIATION_HI;
	parameters.deviation_min = DEFAULT_DEVIATION_LO;
	parameters.z_axis_max = Z_AXIS_THD_HI;
	parameters.z_axis_min = Z_AXIS_THD_LO;

	while (true)
    {
		clear_all();

		if (simulation_running)
		{
			print_green("\n\t\u2B24 Simulation is running!\n");
		}
		else
		{
			print_red("\n\t\u2B24 Simulation isn't running!\n");
		}

        print_blue("***DEFAULT INPUT PARAMETERS***\n");
        printf("XLGYRO_TRAILER_SIZE:\t");
        printf("%d\n", parameters.trailer_size);
        printf("XLGYRO_TRAILER_VALUE:\t");
        printf("%d\n", parameters.trailer_value);
        printf("XLGYRO_PREAMBULE_VALUE:\t");
        printf("%d\n", parameters.preambule_value);
        printf("DEFAULT_DEVIATION_HI:\t");
        printf("%f\n", parameters.deviation_max);
        printf("DEFAULT_DEVIATION_LO:\t");
        printf("%f\n", parameters.deviation_min);
        printf("Z_AXIS_THD_HI:\t\t");
        printf("%f\n", parameters.z_axis_max);
        printf("Z_AXIS_THD_LO:\t\t");
        printf("%f\n", parameters.z_axis_min);
        printf("ROAD_QUALITY:\t\t");
        printf("%d\n", parameters.quality);

        int variant = menu();

        switch (variant) {
			case 1:
				stop_simulation();
				menu_change(&parameters);
				break;
			case 2:
				start_simulation(&parameters);
				break;
			case 3:
				stop_simulation();
				return 0;
        }
    }
	return 0;
}