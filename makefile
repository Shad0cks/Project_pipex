SOURCES_FILES	=	main.c \
					utils/split.c \
					utils/strchr.c \
					utils/strdup.c \
					utils/strjoin.c \
					utils/strlen.c \
					utils/strncmp.c

HEADER			=	header.h

SOURCES			=	$(addprefix ./, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	pipex

CC				=	clang
RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
				$(RM) $(OBJECTS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re