#include "sock_util.h"
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>

extern int errno;

int is_valid_addr(const char* addr)
{
	char* dupaddr = strdup(addr);
	char* token;
	int n=0;
	int ret = 0;
	while((token=strsep(&dupaddr,"."))!=NULL)
	{
		int i=atoi(token);
		if(i==0 && errno!=0)
		{
			ret = 0;
			break;
		}
		if(i<0 | i>255)
		{
			ret = 0;
			break;
		}
		++n;
	}
	if(n!=4)
		ret = 0;
	ret = 1;
	//free(dupaddr);
	return ret;
}

char* host_to_ip(const char* addr)
{
	struct hostent* he = gethostbyname(addr);
	if(he==NULL)
	{
		return NULL;
	}
	char *str = malloc(1024);
	inet_ntop(AF_INET,he->h_addr,str,1024);
	return str;
}

const char* ensure_valid_ip(const char* addr)
{
	if(is_valid_addr(addr))
	{
		return addr;
	}
	return host_to_ip(addr);
}
