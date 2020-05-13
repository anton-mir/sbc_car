#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ROAD_QUALITY = 3;
int XLGYRO_TRAILER_SIZE = 0x04;
int XLGYRO_TRAILER_VALUE = 0x05;
int XLGYRO_PREAMBULE_VALUE = 0xAA55;
float DEFAULT_DEVIATION_HI = 300.0;
float DEFAULT_DEVIATION_LO = -300.0;
float Z_AXIS_THD_HI = 0.4;
float Z_AXIS_THD_LO = -0.4;

int menu();
void menu_change();
void start_simulation();

int main()
{
    while (true)
    {
        system("clear");

        printf("***DEFAULT INPUT PARAMETERS***\n\n");
        printf("XLGYRO_TRAILER_SIZE:\t");
        printf("%d\n", XLGYRO_TRAILER_SIZE);
        printf("XLGYRO_TRAILER_VALUE:\t");
        printf("%d\n", XLGYRO_TRAILER_VALUE);
        printf("XLGYRO_PREAMBULE_VALUE:\t");
        printf("%d\n", XLGYRO_PREAMBULE_VALUE);
        printf("DEFAULT_DEVIATION_HI:\t");
        printf("%f\n", DEFAULT_DEVIATION_HI);
        printf("DEFAULT_DEVIATION_LO:\t");
        printf("%f\n", DEFAULT_DEVIATION_LO);
        printf("Z_AXIS_THD_HI:\t\t");
        printf("%f\n", Z_AXIS_THD_HI);
        printf("Z_AXIS_THD_LO:\t\t");
        printf("%f\n", Z_AXIS_THD_LO);
        printf("ROAD_QUALITY:\t\t");
        printf("%d\n", ROAD_QUALITY);

        int variant = menu();

        switch (variant) {
        case 1: {
            menu_change();
            break;
        }
        case 2: {
            start_simulation();
        }
        case 3: {
            exit(EXIT_SUCCESS);
            break;
        }
        }
    }
}

int menu()
{
    int variant;
    printf("\n1. Change parameters: \n");
    printf("2. Start simulation: \n");
    printf("3. Exit: \n");


    //data entry verification
    while (scanf("%d", &variant) <= 0 || variant < 1 || variant > 3)
    {
        scanf("%*s");
        printf("Incorect input. Try again: ");
    }
    return variant;
}

void menu_change()
{
    int variant_change;

    system("clear");
    printf("***CHANGE INPUT PARAMETERS***\n\n");
    printf("1. XLGYRO_TRAILER_SIZE\n");
    printf("2. XLGYRO_TRAILER_VALUE\n");
    printf("3. XLGYRO_PREAMBULE_VALUE\n");
    printf("4. DEFAULT_DEVIATION_HI\n");
    printf("5. DEFAULT_DEVIATION_LO\n");
    printf("6. Z_AXIS_THD_HI\n");
    printf("7. Z_AXIS_THD_LO\n");
    printf("8. ROAD_QUALITY\n");
    scanf("%d", &variant_change);

    //data entry verification
    while (scanf("%d", &variant_change) <= 0 || variant_change < 1 || variant_change > 8)
    {
        scanf("%*s");
        printf("Incorect input. Try again: ");
        scanf("%d", &variant_change);
    }

    system("clear");

    switch (variant_change) {
    case 1: {
        printf("XLGYRO_TRAILER_SIZE: ");
        scanf("%d", XLGYRO_TRAILER_SIZE);
        break;
    }
    case 2: {
        printf("XLGYRO_TRAILER_VALUE: ");
        scanf("%d", XLGYRO_TRAILER_VALUE);
        break;
    }
    case 3: {
        printf("XLGYRO_PREAMBULE_VALUE: ");
        scanf("%d", XLGYRO_PREAMBULE_VALUE);
        break;
    }
    case 4: {
        printf("DEFAULT_DEVIATION_HI: ");
        scanf("%f", DEFAULT_DEVIATION_HI);
        break;

    }
    case 5: {
        printf("DEFAULT_DEVIATION_LO: ");
        scanf("%f", DEFAULT_DEVIATION_LO);
        break;
    }
    case 6: {
        printf("Z_AXIS_THD_HI: ");
        scanf("%f", Z_AXIS_THD_HI);
        break;
    }
    case 7: {
        printf("Z_AXIS_THD_LO: ");
        scanf("%f", Z_AXIS_THD_LO);
        break;
    }
    case 8: {
        printf("ROAD_QUALITY (1-5): ");
        scanf("%d", ROAD_QUALITY);

        //data entry verification
        while (ROAD_QUALITY < 1 || ROAD_QUALITY > 5)
        {
            printf("Incorect input. Write (1-5): \n");
            scanf("%d", ROAD_QUALITY);
        }
        break;
    }
    }
}

void start_simulation()
{
    system("clear");
    printf("Start simulation\n");

}