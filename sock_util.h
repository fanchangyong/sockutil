#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/*
 * Create TCP Server
 */
int tcp_server(unsigned short port);

/*
 * Accept Connection on fd
 */
int tcp_accept(int fd,struct sockaddr_in* addr);

/*
 * Establish a connection to server
 */
int tcp_conn(const char* addr,unsigned short port);

/*
 * Set backlog count
 */
void set_backlog(int bl);

/*
 * Is Addr Valid IP Address
 */
int is_valid_addr(const char* addr);

/*
 * Host name to IP address(DNS)
 */
char* host_to_ip(const char* addr);
