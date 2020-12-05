#ifndef SERV_H
# define SERV_H

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
// fcntl, select, socket, inet structs, inet
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// read, write
#include <unistd.h>
// strerror
#include <string.h>
#include <errno.h>
// openssl
# include <openssl/ssl.h>
# include <openssl/err.h>

#define FD_FREE		0
#define FD_SERV		1
#define FD_CLIENT	2

#define BUF_SIZE	512

using namespace	std;

typedef struct sockaddr			t_sockaddr;
typedef struct sockaddr_in		t_sockaddr_in;
typedef struct protoent			t_protoent;

typedef struct	s_fd
{
	int			fd;
	int			type;
	bool		isSSL;
	SSL			*sslptr;
	string		buf_read;
	string		buf_write;
}				t_fd;

typedef unordered_map<int, t_fd>			t_fdmap;
typedef unordered_map<int, t_fd>::iterator	t_fdmapit;

typedef struct	s_env
{
	t_fdmap		fds;
	int			port;
	int			sslport;
	SSL_CTX		*sslctx;
	fd_set		fd_read;
	fd_set		fd_write;
	fd_set		fd_error;
}				t_env;

void			srv_initsslctx(t_env *e);
void			srv_create(t_env *e, int port, bool isSSL = false);
void			srv_accept(t_env *e, int s, bool isSSL = false);
void			cli_handshake(t_env *e, int cs);
void			cli_recv(t_env *e, int cs, bool isSSL = false);
void			cli_send(t_env *e, int cs, bool isSSL = false);
int				ssl_errorcallback(const char *str, size_t len, void *u);

#endif
