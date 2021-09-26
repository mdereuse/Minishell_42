CC = clang
CFLAGS = -Wall -Wextra -Werror -I ${INC_DIR}

INC_DIR = ./includes/
SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/

INC_NAME = libft.h
SRCS_NAME = ft_memset.c\
	   ft_bzero.c\
	   ft_memcpy.c\
	   ft_memccpy.c\
	   ft_memmove.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_strlen.c\
	   ft_isalpha.c\
	   ft_isdigit.c\
	   ft_isalnum.c\
	   ft_isascii.c\
	   ft_isprint.c\
	   ft_toupper.c\
	   ft_tolower.c\
	   ft_strchr.c\
	   ft_strrchr.c\
	   ft_strcmp.c\
	   ft_strncmp.c\
	   ft_strlcpy.c\
	   ft_strlcat.c\
	   ft_strnstr.c\
	   ft_atoi.c\
	   ft_calloc.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_split.c\
	   ft_itoa.c\
	   ft_strmapi.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c\
	   ft_strtrim.c\
	   ft_lstnew.c\
	   ft_lstadd_front.c\
	   ft_lstadd_back.c\
	   ft_lstadd_sort.c\
	   ft_lstsize.c\
	   ft_lstlast.c\
	   ft_lstdelone.c\
	   ft_lstclear.c\
	   ft_lstiter.c\
	   ft_lstmap.c\
	   ft_lstat.c\
	   ft_lstremove_if.c\
	   ft_tablen.c\
	   ft_rm_from_tab.c\
	   ft_clean_tab.c\
	   ft_clean_tab_index.c\
	   ft_tablast.c

INC = ${addprefix ${INC_DIR}, ${INC_NAME}}
SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAME}}
OBJS = ${addprefix ${OBJS_DIR}, ${SRCS_NAME:.c=.o}}

NAME = libft.a

all: ${NAME}

${NAME}: ${OBJS_DIR} ${OBJS}
	ar rc $@ ${OBJS}
	ranlib $@

${OBJS_DIR}:
	mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${INC}
	${CC} -o $@ -c $< ${CFLAGS}

clean:
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
