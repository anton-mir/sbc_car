#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>

static struct sockaddr_in client;
static int broadcast, sock;

void reporter_init(const char *address, const int port)
{
    struct ifaddrs *ifaddr;
    struct ifaddrs *ifa;

    broadcast = 0;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0){
        printf("can't create reporter socket: %d\n", errno);
        exit(1);
    }

    bzero((char*)&client, sizeof(client));

    client.sin_family = AF_INET;
    inet_pton(AF_INET, address, &(client.sin_addr));
    client.sin_port = htons(port);

    if (getifaddrs(&ifaddr) < 0) {
        printf("Fail to getifaddrs(); errno: %d", errno);
        close(sock);
        exit(1);
    }

    /* Check if client address is broadcast */
    struct sockaddr_in *broadcastAddress;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        if (ifa->ifa_addr->sa_family != AF_INET6) {
            broadcastAddress = (struct sockaddr_in *)ifa->ifa_ifu.ifu_broadaddr;
            if (broadcastAddress->sin_addr.s_addr == client.sin_addr.s_addr) {
                broadcast = 1;
                break;
            }
        }
    }
    freeifaddrs(ifaddr);

    if (broadcast) {
        /* Set permissions to send broadcast packets */
        int broadcastPermission = 1;

        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission)) < 0) {
            printf("Fail to set SO_BROADCAST for socket: %d; errno: %d", sock, errno);
            close(sock);
            exit(1);
        }
    } else {
        if (connect(sock, (struct sockaddr*)&client, sizeof(client)) < 0) {
            printf("FAIL to connect to client %s:%d socket\n", inet_ntoa(client.sin_addr), port);

            exit(1);
        }
    }
}

void report(const char *report, const int port)
{
    if (!broadcast) {
        if (send(sock, report, strlen(report), 0) < 0) {
            printf("FAIL to send message to client %s:%d socket, error: %d\n", inet_ntoa(client.sin_addr), port, errno);
        }
    } else {
        if (sendto(sock, report, strlen(report), 0, (struct sockaddr*)&client, sizeof(client)) < 0) {
            printf("FAIL to send broadcast message %s:%d socket, error: %d\n", inet_ntoa(client.sin_addr), port, errno);
        } else {
            printf("BROADCAST SENT SUCCESSFULLY");
        }
    }
}
