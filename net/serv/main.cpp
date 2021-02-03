#include "serv.hpp"
#include <signal.h>

/*
**	simple nonblocking server for client server connection
**	you can test connect from nc/netcat and openssl client
**	usage:		./serv
**	connect:	nc localhost 4422
**	sslconnect:	openssl s_client -connect localhost:4433
*/

int		main(void)
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		error_exit("signal error");

	t_env	e;

	e.port = 4422;
	e.sslport = 4433;
	srv_initsslctx(&e);
	srv_create(&e, e.port);
	srv_create(&e, e.sslport, true);
	while (1)
	{
		int lastfd = 0;
		FD_ZERO(&(e.fd_read));
		FD_ZERO(&(e.fd_write));
		FD_ZERO(&(e.fd_error));
		for (t_fdmapit it = e.fds.begin(); it != e.fds.end(); it++)
		{
			FD_SET(it->first, &(e.fd_read));
			if (!it->second.buf_write.empty())
				FD_SET(it->first, &(e.fd_write));
			FD_SET(it->first, &(e.fd_error));
			lastfd = max(lastfd, it->first);
		}
		int readyfds = select(lastfd + 1, &(e.fd_read), &(e.fd_write), &(e.fd_error), NULL);
		if (readyfds < 0)
		{
			cerr << "select failed" << endl;
			exit(1);
		}
		for (int fd = 0; readyfds > 0 && fd <= lastfd; fd++)
		{
			bool	isread = FD_ISSET(fd, &(e.fd_read));
			bool	iswrite = FD_ISSET(fd, &(e.fd_write));
			bool	iserror = FD_ISSET(fd, &(e.fd_error));

			if (isread || iswrite || iserror)
				readyfds--;
			if (iserror)
			{
				cerr << "OOB data on fd " << fd << endl;
				continue ;
			}
			if (isread)
			{
				if (e.fds[fd].type == FD_SERV)
					srv_accept(&e, fd, e.fds[fd].isSSL);
				else
				{
					// only allow non ssl and handshaked ssl data exchange
					if (!(e.fds[fd].isSSL) || (e.fds[fd].isSSL &&
						SSL_is_init_finished(e.fds[fd].sslptr)))
						cli_recv(&e, fd, e.fds[fd].isSSL);
					else
						cli_handshake(&e, fd);
				}
			}
			if (iswrite)
			{
				if (!(e.fds[fd].isSSL) || (e.fds[fd].isSSL &&
					SSL_is_init_finished(e.fds[fd].sslptr)))
					cli_send(&e, fd, e.fds[fd].isSSL);
				else
					cli_handshake(&e, fd);
			}
		}
	}
	return (0);
}
