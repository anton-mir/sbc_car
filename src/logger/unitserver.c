#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

static int reg_serv_fd;

int open_reg_serv(int reg_port)
{
    struct sockaddr_in server;
    int rc;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(reg_port);

    reg_serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!reg_serv_fd) {
        printf("Can`t create socket for registration server\n");
        return -1;
    }

    rc = bind(reg_serv_fd, (struct sockaddr *)&server, sizeof(server));
    if (!rc) {
        printf("Bind failed\n");
        return -1;
    }

    return 0;
}

int wait_on_any_unit_req(int *client_sock)
{
    #define REG_MAX_CLIENTS_CNT 5
    #define REG_REQ_MAX_LEN 5
    #define REG_REQUEST     ((char *)"GETID")

    char request[REG_REQ_MAX_LEN] = "none";
    struct sockaddr sender;
    socklen_t sendsize = sizeof(sender);
    bzero(&sender, sizeof(sender));

    listen(reg_serv_fd, REG_MAX_CLIENTS_CNT);

    printf("Waiting for incoming connections...\n");
    *client_sock = accept(reg_serv_fd,
                        (struct sockaddr *)&sender,
                        (socklen_t*)&sendsize);

    int read_bytes = recv(*client_sock, request, REG_REQ_MAX_LEN, 0);

    printf("Some request was received\n");

    if ((read_bytes != REG_REQ_MAX_LEN) ||
        (0 != strncmp(&request[0], REG_REQUEST, read_bytes)))  {
        printf("Request is wrong: %s\n", request);
        return -1;
    }
    printf("Registration request was received: %s\n", request);

    return 0;
}
