#include "sock_util.h"
#include <stdlib.h>

static int backlog = 5;

int tcp_server(unsigned short port)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(fd,(struct sockaddr*)&addr,sizeof(addr))==-1)
	{
		return -1;
	}

	if( listen(fd,backlog) == -1 )
	{
		return -1;
	}
	return fd;
}

int tcp_accept(int fd,struct sockaddr_in* addr)
{
	socklen_t len = sizeof(*addr);
	int cli_sock;

	cli_sock = accept(fd,(struct sockaddr*)addr,&len);
	if(cli_sock == -1)
	{
		return -1;
	}

	return cli_sock;
}

int tcp_conn(const char* host,unsigned short port)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(is_valid_addr(host))
	{
		addr.sin_addr.s_addr = inet_addr(host);
	}
	else
	{
		char* ip = host_to_ip(host);
		addr.sin_addr.s_addr = inet_addr(ip);
		//free(ip);
	}

	socklen_t len = sizeof(addr);

	if(-1==connect(fd,(struct sockaddr*)&addr,len))
	{
		return -1;
	}

	return fd;
}

void set_backlog(int bl)
{
	backlog = bl;
}

