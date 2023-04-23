SRCS = 	parsing/main.c \
		parsing/fill_types.c \
		parsing/check_syntax.c\
		parsing/set_states.c\
		parsing/files.c\
		parsing/lst_init.c\
		parsing/here_doc.c\
		parsing/splite_pipe_space.c\
		parsing/env_link.c\
		exction/builtins/echo.c \
		exction/builtins/pwd.c \
		exction/builtins/cd.c \
		exction/execve/execution_utils.c \
		exction/pipes/pipes.c \
		libft/ft_atoi.c     libft/ft_isprint.c               libft/ft_memmove.c     libft/ft_strchr.c    libft/ft_strmapi.c  libft/ft_toupper.c\
		libft/ft_bzero.c    libft/ft_itoa.c                  libft/ft_memset.c      libft/ft_strdup.c    libft/ft_strncmp.c \
		libft/ft_calloc.c        libft/ft_putchar_fd.c  libft/ft_striteri.c  libft/ft_strnstr.c \
		libft/ft_isalnum.c   libft/ft_putendl_fd.c  libft/ft_strjoin.c   libft/ft_strrchr.c \
		libft/ft_isalpha.c       libft/ft_memchr.c         libft/ft_putnbr_fd.c   libft/ft_strlcat.c   libft/ft_strtrim.c\
		libft/ft_isascii.c     libft/ft_memcmp.c         libft/ft_putstr_fd.c   libft/ft_strlcpy.c   libft/ft_substr.c\
		libft/ft_isdigit.c        libft/ft_memcpy.c         libft/ft_split.c       libft/ft_strlen.c    libft/ft_tolower.c\


NAME = minishell
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	$(CC) $(CFLAGS) $(SRCS) -lreadline  -o $(NAME) 
clean:
	$(RM) $(O_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run :
	make
	clear
	./minishell
norm:
	@norminette

.PHONY: all clean fclean re norm
