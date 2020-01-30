#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "unitserver.h"
#include "sender.h"
#include "reporter.h"

#define UPD_TIME_MS 10

static struct sockaddr_in controller;
static int sock;

void netw_init(const int port)
{
    int optval = 1;
    struct timeval timeout = { 0 };

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        exit(1);

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        printf("Failed to set timeout for server socket options, err: %d\n", errno);
        exit(1);
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        printf("Failed to set address reuse mode for server socket options, err: %d\n", errno);
        exit(1);
    }

    bzero((char*)&controller, sizeof(controller));
    controller.sin_family = AF_INET;
    controller.sin_addr.s_addr = htonl(INADDR_ANY);
    controller.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*) &controller, sizeof(controller)) < 0) {
        printf("Failed to bind to server socket\n");
            exit(1);
    }
}

void handle_reports(const char *message, const char *ip, const int port)
{
    report(message, port);
    printf("handleReports: %15s:%d <- %s\n", ip, port, message);
    usleep(UPD_TIME_MS * 1000);
}

#if 0
void netw_main(double lat, double lon, double speed, double course)
{
    int client_socket = 0;
    const char *reg_ip = "127.0.0.1";
    const int reg_port = 40880;
    const char *unit_port = "40701";
    char *gen_json;

    netw_init(reg_port);
    open_reg_serv(reg_port);

    wait_on_any_unit_req(&client_socket);
    printf("client_socket = %d\n", client_socket);

    write(client_socket, unit_port, strlen(unit_port));

    gen_json = generate_json(1, "ambulance", lat, lon, speed, course);
    printf("gen_json = %s\n", gen_json);

    reporter_init(reg_ip, reg_port);
    handle_reports(gen_json, reg_ip, reg_port);

    free(gen_json);
}
#endif
