CC = clang
CFLAGS = -Wall -Wextra -Werror -I ${INC_DIR} -I ${LIBFT_INC_DIR}
LDFLAGS = -L./libft -lft

LIBFT_DIR = ./libft/
LIBFT_INC_DIR = ./libft/includes
LIBFT = ./libft/libft.a

INC_DIR = ./includes/
SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/
SRCS_NAMES = main.c \
	   pattern.c \
	   pattern_2.c \
	   pattern_3.c \
	   pattern_4.c \
	   set_env_list.c \
	   fix_pwd_oldpwd.c \
	   add_env_var.c \
	   initialize_lst_word.c \
	   increment_shlvl.c \
	   set_env_tab.c \
	   set_path.c \
	   set_cwd.c \
	   minishell.c \
	   sighandler.c \
	   line_parsing.c \
	   add_command.c \
	   create_command_str.c \
	   create_command_argv.c \
	   check_syntax.c \
	   launching_loop.c \
	   info_command.c \
	   exec_command.c \
	   prepare_command.c \
	   set_redirection.c \
	   epure_argv.c \
	   replace_variable.c \
	   replace_variable_2.c \
	   replace_variable_3.c \
	   sup_quote.c \
	   actualize_lst_word.c \
	   open_redirection.c \
	   exec_command_builtin.c \
	   info_env_var.c \
	   manipulate_env.c \
	   pwd_and_oldpwd.c \
	   environment_actualization.c \
	   builtin_cd.c \
	   builtin_echo.c \
	   builtin_env.c \
	   builtin_pwd.c \
	   builtin_exit.c \
	   builtin_export.c \
	   builtin_export_utils.c \
	   builtin_unset.c \
	   exec_command_default.c \
	   set_fst_arg.c \
	   child_process.c \
	   add_process.c \
	   check_path.c \
	   clean.c \
	   error.c \
	   quit.c \
	   get_next_line.c
INC_NAMES = minishell.h
SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAMES}}
OBJS = ${addprefix ${OBJS_DIR}, ${SRCS_NAMES:.c=.o}}
INC = ${addprefix ${INC_DIR}, ${INC_NAMES}}
NAME = minishell

all: ${NAME}

${NAME}: ${OBJS_DIR} ${LIBFT} ${OBJS}
	${CC} -o $@ ${OBJS} ${CFLAGS} ${LDFLAGS}

${OBJS_DIR}:
	mkdir ${OBJS_DIR}

${LIBFT}:
	${MAKE} -C libft

${OBJS_DIR}exec_command.o: ${INC_DIR}builtins.h

${OBJS_DIR}error.o: ${INC_DIR}error.h

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${INC}
	${CC} -o $@ -c $< ${CFLAGS}

clean:
	${MAKE} -C libft clean
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -f ${LIBFT} ${NAME}

re: fclean all

.PHONY: all clean fclean re
