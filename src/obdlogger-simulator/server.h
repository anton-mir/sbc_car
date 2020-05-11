#ifndef SERVER_H
#define SERVER_H

#define HOST "127.0.0.1"
#define PORT 11333

int create_server();
int close_server();
void send_packet(uint8_t *data, uint32_t len);

#endif