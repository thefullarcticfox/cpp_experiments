#include "serv.hpp"

int		ssl_errorcallback(const char *str, size_t len, void *u)
{
	(void)u;
	(void)len;
	cerr << str;
	return (1);
}

void	srv_initsslctx(t_env *e)
{
	SSL_library_init();
	SSL_load_error_strings();
	if (!(e->sslctx = SSL_CTX_new(TLS_server_method())))
	{
		ERR_print_errors_cb(ssl_errorcallback, NULL);
		exit(1);
	}
	if (SSL_CTX_set_ecdh_auto(ctx, 1) <= 0)
	{
		ERR_print_errors_cb(ssl_errorcallback, NULL);
		exit(1);
	}
	/* Set the key and cert */
	if (SSL_CTX_use_certificate_file(e->sslctx, "./test.crt", SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_cb(ssl_errorcallback, NULL);
		exit(1);
	}
	if (SSL_CTX_use_PrivateKey_file(e->sslctx, "./test.key", SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_cb(ssl_errorcallback, NULL);
		exit(1);
	}
}

void	cli_handshake(t_env *e, int cs)
{
	int		handshake = SSL_accept(e->fds[cs].sslptr);

	if (handshake == 1)
		cout << "Successfully handshaked with client " << cs << std::endl;
	// continue if handshake need more actions (until it returns 1)
	if (handshake != 1)
	{
		// check if handshake need more actions or gone wrong by SSL_get_error
		int	err = SSL_get_error(e->fds[cs].sslptr, handshake);
		// SSL_ERROR_WANT_READ/WRITE in case handshake needs another round
		if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE)
		{
			// drop the connection if handshake gone wrong
			std::cerr << "SSL handshake failed for client " << cs << std::endl;
			ERR_print_errors_cb(ssl_errorcallback, NULL);
			// we shouldn't call SSL_shutdown because it's already fatal
			SSL_free(e->fds[cs].sslptr);
			FD_CLR(cs, &(e->fd_read));
			FD_CLR(cs, &(e->fd_write));
			FD_CLR(cs, &(e->fd_error));
			close(cs);
			e->fds.erase(cs);
		}
	}
}
