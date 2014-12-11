#include "ev.h"
#include "enet.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT	8000
#define NO_OF_FDS	10

typedef struct {
	int i;
} context_t;

void read_data_handle(ev_event_loop * el, int fd, void *privdata, int mask)
{

	return;
}

void accept_tcp_handle(ev_event_loop * el, int fd, void *privdata, int mask)
{
	int cfd, cport;
	char ip_addr[128] = { 0 };
	context_t *ctx = (context_t *)privdata;

	cfd = enet_tcp_accept(NULL, fd, ip_addr, 128, &cport);

	if (cfd == ENET_ERR) {
		return;
	}
	if (cfd > NO_OF_FDS) {
		ev_delete_file_event(el, fd, EV_READABLE);
		close(fd);
	}

	if (ev_create_file_event(el, cfd, EV_READABLE,
				 read_data_handle, ctx) == EV_ERR) {
		fprintf(stderr, "Accept new socket error!");
		return;
	}

	return;
}


int main(void)
{
	int fd;
	int backlog = 10;
	context_t ctx;
	ev_event_loop *event_loop;

	fd = enet_tcp_server(NULL, PORT, NULL, backlog);

	event_loop = ev_create_event_loop(512);
	if (ev_create_file_event(event_loop, fd, EV_READABLE,
				accept_tcp_handle, &ctx) == EV_ERR) {
		fprintf(stderr, "ev create failed!\n");
		return -1;
	}
	ev_main(event_loop);
	ev_delete_event_loop(event_loop);

	return 0;
}
