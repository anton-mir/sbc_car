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
    printf("handleReports: %15s:%d <- %s\n\n", ip, port, message);
    usleep(UPD_TIME_MS * 1000);
}
