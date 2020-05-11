#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "xlgyro_data_helper.h"
#include "console_helper.h"
#include "server.h"

static bool server_run = false;
static int main_socket = 0;
static int client_fd = 0;
static pthread_t s_thread;
static void *server_handler() {
    int client_socket, socket_options;
    struct sockaddr_in server, client;

    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket == -1) {

        #ifdef DEBUG_LOG
        print_red("Socket start failed!");
        perror("ERROR");
        #endif

        return NULL;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Socket start successed!");
        #endif
    }

    /*if (setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&socket_options, sizeof(socket_options))) {

        #ifdef DEBUG_LOG
        print_red("Socket option set failed!");
        perror("ERROR");
        #endif

        close(main_socket);
        return NULL;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Socket option set successed!");
        #endif
    }*/

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(HOST);
    server.sin_port = htons(PORT);

    if (bind(main_socket, (struct sockaddr*) &server, sizeof(server)) < 0) {

        #ifdef DEBUG_LOG
        print_red("Bind failed!");
        perror("ERROR");
        #endif

        close(main_socket);
        return NULL;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Bind successed!");
        #endif
    }
    
    if (listen(main_socket, 2) < 0) {

        #ifdef DEBUG_LOG
        print_red("Server listen failed!");
        perror("ERROR");
        #endif
        
        close(main_socket);
        return NULL;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Server listen successed!");
        #endif
    }

    #ifdef DEBUG_LOG
    print_default("\nWaiting for connections...");
    #endif

    fd_set rset;
    FD_ZERO(&rset);
    
    while (true)
    {
        FD_SET(main_socket, &rset); 
        if (select(main_socket + 1, &rset, NULL, NULL, NULL) < 0) {

            #ifdef DEBUG_LOG
            print_red("Select failed!");
			perror("ERROR");
            #endif

            break;
        }
        else 
        {
            #ifdef DEBUG_LOG
            print_green("Select successed!");
            #endif
        }

        if (FD_ISSET(main_socket, &rset)) { 
            int len = sizeof(struct sockaddr_in);
            client_socket = accept(main_socket, (struct sockaddr*) &client, (socklen_t*) &len);
            if (client_socket < 0) {

                #ifdef DEBUG_LOG
                print_red("Accept failed!");
                perror("ERROR");
                #endif

                break;
            }
            else 
            {
                #ifdef DEBUG_LOG
                print_green("\nConnection accept successed!");
                #endif
            }
            client_fd = client_socket;

            if (read(client_socket, NULL, 32) == 0)
            {
                close(client_socket);
                client_fd = 0;

                #ifdef DEBUG_LOG
                print_yellow("No client.");
                #endif
            }
        }
        pthread_testcancel();
    }
    close(main_socket);
    pthread_exit(0);
}

int create_server()
{
    if (pthread_create(&s_thread, NULL, server_handler, NULL) < 0) {

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

    server_run = true;

    return 0;
}

int close_server()
{
    if (server_run == false) return -1;
    close(main_socket);

    if (pthread_cancel(s_thread) < 0) {

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

    if (pthread_join(s_thread, NULL) < 0) {
        
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

    client_fd = 0;
    server_run = false;

    return 0;
}

void send_packet(uint8_t *data, uint32_t len)
{
    if (data == NULL) 
    {

        #ifdef DEBUG_LOG
        print_red("`data` is NULL!");
        #endif

        return;
    }
    if (client_fd == 0) 
    {

        #ifdef DEBUG_LOG
        print_red("Client disconected!");
        #endif

        return;
    }

    if (send(client_fd, data, len, 0) < 0) 
    {

        #ifdef DEBUG_LOG
        print_red("Packet send failed!");
		perror("ERROR");
        #endif

        return;
    }
    else 
    {
        #ifdef DEBUG_LOG
        print_green("Packet send successed!");
        #endif
    }
}