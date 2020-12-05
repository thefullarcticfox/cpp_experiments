NAME		= serv
SRCS		= main.cpp srv_base.cpp srv_ssl.cpp
OBJS		= $(SRCS:.cpp=.o)
CC			= clang++
CFLAGS		= -I. -g3 -Wall -Wextra -Werror
EXEFLAGS	= $(CFLAGS) -lssl -lcrypto
SSLCERT		= ./test.crt ./test.key

all:		$(NAME) $(SSLCERT)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(EXEFLAGS)

%.o:%.cpp	$(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SSLCERT):
	@echo "generating tls certificate..."
	@openssl req -x509 -nodes -days 365 -newkey rsa:4096 \
		-keyout $(word 2,$(SSLCERT)) -out $(word 1,$(SSLCERT)) \
		-subj "/C=US/ST=State/L=Town/O=13/OU=37/CN=serv"

clean:
	/bin/rm -f $(OBJS)

fclean:		clean
	/bin/rm -f $(NAME) $(SSLCERT)

re:			fclean all
