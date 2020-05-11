#include <iostream>
#include <cstdlib>

using namespace std;

int ROAD_QUALITY = 3;
string XLGYRO_TRAILER_SIZE = "0x04";
string XLGYRO_TRAILER_VALUE = "0x05";
string XLGYRO_PREAMBULE_VALUE = "0xAA55";
float DEFAULT_DEVIATION_HI = 300.0;
float DEFAULT_DEVIATION_LO = -300.0;
float Z_AXIS_THD_HI = 0.4;
float Z_AXIS_THD_LO = -0.4;

int menu(); 
void menu_change();

int main()
{
    system("cls");

    cout << "***DEFAULT INPUT PARAMETERS***\n\n";
    cout << "XLGYRO_TRAILER_SIZE:\t" << XLGYRO_TRAILER_SIZE << endl;
    cout << "XLGYRO_TRAILER_VALUE:\t" << XLGYRO_TRAILER_VALUE << endl;
    cout << "XLGYRO_PREAMBULE_VALUE:\t" << XLGYRO_PREAMBULE_VALUE << endl;
    cout << "DEFAULT_DEVIATION_HI:\t" << DEFAULT_DEVIATION_HI << endl;
    cout << "DEFAULT_DEVIATION_LO:\t" << DEFAULT_DEVIATION_LO << endl;
    cout << "Z_AXIS_THD_HI:\t\t" << Z_AXIS_THD_HI << endl;
    cout << "Z_AXIS_THD_LO:\t\t" << Z_AXIS_THD_LO << endl;
    cout << "ROAD_QUALITY:\t\t" << ROAD_QUALITY << endl;

    int variant = menu();
    switch (variant) {
    case 1: {
        menu_change();
        main();
        break;
        }
    case 2: {
        exit(EXIT_SUCCESS);
        break;
    }
    }
}

int menu()
{
    int variant;
    cout << "\n1. Change parameters: " << endl;
    cout << "2. Exit: " << endl;
    cin >> variant;
    return variant;
}

void menu_change()
{
    int variant_change;

    system("cls");
    cout << "***CHANGE INPUT PARAMETERS***\n\n";
    cout << "1. XLGYRO_TRAILER_SIZE\n";
    cout << "2. XLGYRO_TRAILER_VALUE\n";
    cout << "3. XLGYRO_PREAMBULE_VALUE\n";
    cout << "4. DEFAULT_DEVIATION_HI\n";
    cout << "5. DEFAULT_DEVIATION_LO\n";
    cout << "6. Z_AXIS_THD_HI\n";
    cout << "7. Z_AXIS_THD_LO\n";
    cout << "8. ROAD_QUALITY\n";
    cin >> variant_change;

    system("cls");

    switch (variant_change) {
    case 1: {
        cout << "XLGYRO_TRAILER_SIZE: ";
        cin >> XLGYRO_TRAILER_SIZE;
        return;
    }
    case 2: {
        cout << "XLGYRO_TRAILER_VALUE: ";
        cin >> XLGYRO_TRAILER_VALUE;
        return;
    }
    case 3: {
        cout << "XLGYRO_PREAMBULE_VALUE: ";
        cin >> XLGYRO_PREAMBULE_VALUE;
        return;
    }
    case 4: {
        cout << "DEFAULT_DEVIATION_HI: ";
        cin >> DEFAULT_DEVIATION_HI;
        return;
    }
    case 5: {
        cout << "DEFAULT_DEVIATION_LO: ";
        cin >> DEFAULT_DEVIATION_LO;
        return;
    }
    case 6: {
        cout << "Z_AXIS_THD_HI: ";
        cin >> Z_AXIS_THD_HI;
        return;
    }
    case 7: {
        cout << "Z_AXIS_THD_LO: ";
        cin >> Z_AXIS_THD_LO;
        return;
    }
    case 8: {
        cout << "ROAD_QUALITY (1-5): ";
        cin >> ROAD_QUALITY;
        return;
    }
    }
 
}