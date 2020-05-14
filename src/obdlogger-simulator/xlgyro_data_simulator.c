#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "xlgyro_data_helper.h"
#include "server.h"

static pthread_t s_thread;
static bool simulator_run = false;

static void *simulator_handler(void *parameters) 
{
    while (true)
    {
        XLGYRO_PACKET_S packet = generate_packet(*((XLGYRO_PACKET_PARAMETERS_S*)parameters));
		send_packet((uint8_t*)&packet, sizeof(XLGYRO_PACKET_S));
        sleep(1);
        
        pthread_testcancel();
    }
    pthread_exit(0);
}

int create_simulator(XLGYRO_PACKET_PARAMETERS_S *parameters)
{
    if (simulator_run == true) return -2;
    if (pthread_create(&s_thread, NULL, simulator_handler, parameters) == 0) {

        #ifdef DEBUG_LOG
        print_red("Thread create failed!");
        perror("ERROR");
        #endif

        return -1;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Thread create successed!");
        #endif
    }
    simulator_run = true;

    return 0;
}

int close_simulator()
{
    if (simulator_run == false) return -1;
    if (pthread_cancel(s_thread) == 0) {

        #ifdef DEBUG_LOG
        print_red("Thread cancel failed!");
        perror("ERROR");
        #endif

        return -1;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Thread cancel successed!");
        #endif
    }

    if (pthread_join(s_thread, NULL) == 0) {
        
        #ifdef DEBUG_LOG
        print_red("Thread join failed!");
        perror("ERROR");
        #endif

        return -1;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Thread join successed!");
        #endif
    }

    simulator_run = false;

    return 0;
}