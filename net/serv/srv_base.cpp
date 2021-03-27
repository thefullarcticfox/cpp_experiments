#include "serv.hpp"
#include <sstream>

void	srv_create(t_env* e, int port, bool isSSL)
{
	int				s;
	t_sockaddr_in	sin;
	t_protoent*		pe;
	t_fd			server;
	int				optval = 1;

	if (!(pe = getprotobyname("tcp")))
	{
		cerr << "getprotobyname error: " << strerror(errno) << endl;
		exit(1);
	}
	if ((s = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
	{
		cerr << "socket error: " << strerror(errno) << endl;
		exit(1);
	}
	// set nonblock
	if (fcntl(s, F_SETFL, O_NONBLOCK) < 0)
	{
		cerr << "fcntl error: " << strerror(errno) << endl;
		exit(1);
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		cerr << "bind error: " << strerror(errno) << endl;
		exit(1);
	}
	if (bind(s, (t_sockaddr*)&sin, sizeof(sin)) < 0)
	{
		cerr << "bind error: " << strerror(errno) << endl;
		exit(1);
	}
	if (listen(s, 42) < 0)
	{
		cerr << "listen error: " << strerror(errno) << endl;
		exit(1);
	}
	server.fd = s;
	server.type = FD_SERV;
	server.isSSL = isSSL;
	if (server.isSSL)
		cout << "SSL";
	cout << "Server created on fd " << s << " (port " << port << ")" << endl;
	e->fds[s] = server;
}

void	send_all(t_env* e, int cs, const string& msg)
{
	ostringstream	oss;
	oss << "Client " << cs << " " << msg;

	for (t_fdmapit i = e->fds.begin(); i != e->fds.end(); i++)
		if ((i->second.type == FD_CLIENT) && (i->first != cs))
			i->second.buf_write += oss.str();
}

void	srv_accept(t_env* e, int s, bool isSSL)
{
	int				cs;
	t_sockaddr_in	csin;
	socklen_t		csin_len;
	t_fd			client;

	csin_len = sizeof(csin);
	if ((cs = accept(s, (t_sockaddr*)&csin, &csin_len)) < 0)
	{
		cerr << "accept error: " << strerror(errno) << endl;
		exit(1);
	}
	// set nonblock
	if (fcntl(cs, F_SETFL, O_NONBLOCK) < 0)
	{
		cerr << "fcntl error: " << strerror(errno) << endl;
		exit(1);
	}
	cout << "Client " << cs << " from " <<
		inet_ntoa(csin.sin_addr) << ":" << ntohs(csin.sin_port) <<
		" accepted" << endl;
	client.fd = cs;
	client.type = FD_CLIENT;
	client.isSSL = isSSL;
	e->fds[cs] = client;

	send_all(e, cs, "connected\n");

	if (isSSL)
	{
		if (!(e->fds[cs].sslptr = SSL_new(e->sslctx)))
		{
			ERR_print_errors_cb(ssl_errorcallback, NULL);
			exit(1);
		}
		if (SSL_set_fd(e->fds[cs].sslptr, cs) < 1)
		{
			ERR_print_errors_cb(ssl_errorcallback, NULL);
			exit(1);
		}
	}
}

void	cli_recv(t_env* e, int cs, bool isSSL)
{
	ssize_t		r;
	char		buf_read[BUF_SIZE + 1];

	if (isSSL)
		r = SSL_read(e->fds[cs].sslptr, buf_read, BUF_SIZE);
	else
		r = recv(cs, buf_read, BUF_SIZE, 0);
	if (r >= 0)
		buf_read[r] = 0;
	if (r > 0)
	{
		e->fds[cs].buf_read += buf_read;
		if (e->fds[cs].buf_read[e->fds[cs].buf_read.length() - 1] == '\n')
		{
			cout << "Client " << cs << " sent " << e->fds[cs].buf_read;
			send_all(e, cs, "sent: " + e->fds[cs].buf_read);
			e->fds[cs].buf_read.erase();
		}
	}
	else
	{
		if (isSSL)
		{
			/* for ssl may be recoverable */
			int	err = SSL_get_error(e->fds[cs].sslptr, r);
			if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE)
				return ;
			ERR_print_errors_cb(ssl_errorcallback, NULL);
			SSL_free(e->fds[cs].sslptr);
			std::cout << "SSL";
		}
		close(cs);
		FD_CLR(cs, &(e->fd_read));
		FD_CLR(cs, &(e->fd_write));
		FD_CLR(cs, &(e->fd_error));
		e->fds.erase(cs);
		send_all(e, cs, "disconnected\n");
		cout << "Client " << cs << " disconnected" << endl;
	}
}

void	cli_send(t_env* e, int cs, bool isSSL)
{
	ssize_t		r;

	if (isSSL)
		r = SSL_write(e->fds[cs].sslptr, e->fds[cs].buf_write.c_str(), e->fds[cs].buf_write.length());
	else
		r = send(cs, e->fds[cs].buf_write.c_str(), e->fds[cs].buf_write.length(), 0);
	e->fds[cs].buf_write.erase();
	if (r <= 0)
	{
		if (isSSL)
		{
			/* for ssl may be recoverable */
			int	err = SSL_get_error(e->fds[cs].sslptr, r);
			if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE)
				return ;
			ERR_print_errors_cb(ssl_errorcallback, NULL);
			SSL_free(e->fds[cs].sslptr);
			std::cout << "SSL";
		}
		close(cs);
		FD_CLR(cs, &(e->fd_read));
		FD_CLR(cs, &(e->fd_write));
		FD_CLR(cs, &(e->fd_error));
		e->fds.erase(cs);
		send_all(e, cs, "disconnected\n");
		cout << "Client " << cs << " disconnected" << endl;
	}
}
