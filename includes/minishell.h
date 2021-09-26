/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 20:38:13 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 08:10:48 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define FAILURE 1
# define ERROR_SYNTAX 258
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_CMD_EXEC 126
# define BREAK_GNL 2
# define SUCCESS_GNL 1
# define EOF_GNL 0
# define FAILURE_GNL -1
# define ERROR_NO_OLDPWD -2
# define ERROR_NO_HOME -3
# define ERROR_KEY_NOT_FOUND -4
# define ERROR_VALUE_NOT_FOUND -5
# define ERROR_EXIT_NB_ARGS -6
# define ERROR_EXIT_NUM_ARG -7
# define ERROR_INVALID_KEY -8
# define ERROR_FTL -9

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include "libft.h"

bool					g_sigint_shell;
bool					g_sigint_command;
pid_t					g_pid;

typedef struct stat		t_stat;

typedef enum			e_redir_mode
{
	COMMAND_ENTRY,
	FILE_ENTRY,
	COMMAND_EXIT,
	FILE_ER_EXIT,
	FILE_AP_EXIT
}						t_redir_mode;

typedef struct			s_redir
{
	t_redir_mode		mode;
	char				*filename;
	int					fd;
}						t_redir;

typedef struct			s_process
{
	pid_t				pid;
	int					status;
}						t_process;

typedef struct			s_command
{
	char				*str;
	char				*previous_word;
	char				*last_word;
	char				**argv;
	int					argc;
	char				*fst_arg;
	t_list				*redir_list;
	int					pipe_out[2];
	int					entry_fd;
	int					exit_fd;
}						t_command;

typedef struct			s_env_var
{
	char				*key;
	char				*value;
}						t_env_var;

typedef struct			s_mini
{
	char				**env_tab;
	t_list				*env_list;
	t_list				*com_list;
	t_list				*process_list;
	char				**path;
	char				*pwd;
	char				*oldpwd;
	char				*cwd;
	int					lst_status;
	char				*lst_word;
	bool				exit_stop;
}						t_mini;

void					initialize_mini(t_mini *mini);

int						is_blank(char c);
bool					is_white_space(char c);
bool					is_separator_pattern(char *str);
bool					is_redirection_pattern(char *str);
bool					is_special_pattern(char *str);
bool					is_escapable_char(char c);
bool					is_effective_antislash(char *str, int index);
bool					is_escaped(char *str, int index);
bool					inside_quote(char *str, int index);
bool					inside_simple_quote(char *str, int index);
bool					is_new_arg(char *str, int index);
bool					is_new_command(char *str, int index);
bool					is_end_command(char *str, int index);
bool					is_new_variable(char *str, int index);
bool					is_end_variable(char *str, int index);
bool					is_end_key(char *str, int index);
bool					is_initialized(char *env_line);
bool					is_modified(char *env_line);

char					*get_key_from_env_line(char *env_line);
char					*get_value_from_env_line(char *env_line);
int						add_new_env_var(char *env_line, t_mini *mini);

int						set_env_list(t_mini *mini, char **env);

int						fix_pwd_oldpwd(t_mini *mini);

int						initialize_lst_word(t_mini *mini);

int						increment_shlvl(t_mini *mini);

int						set_env_tab(t_mini *mini);

int						set_path(t_mini *mini);

int						set_cwd(t_mini *mini);

void					display_prompt(void);
void					minishell(t_mini *mini);

void					sigint_handler_shell(int sig);
void					sigint_handler_command(int sig);
void					sigquit_handler_shell(int sig);
void					sigquit_handler_command(int sig);

int						parse_line(char *line, t_mini *mini);

int						add_new_command(char *line, t_mini *mini);

char					*create_new_command_str(char *line);

char					**create_new_command_argv(char *str);

bool					check_syntax_line_ok(t_mini *mini);

bool					is_entry_mode(t_redir_mode mode);
bool					is_exit_mode(t_redir_mode mode);
bool					has_command_exit(t_command *command);
bool					has_command_entry(t_command *command);
bool					is_in_pipe_line(t_command *command);

void					launching_loop(t_mini *mini);

int						exec_command(t_command *command, t_command *prv_command,
						t_mini *mini);

int						prepare_command(t_command *command,
						t_command *prv_command, t_mini *mini);

int						set_redirection(t_command *command, t_mini *mini);

int						epure_argv(t_command *command);

char					*create_new_arg_with_var(char *old_arg, int index_char,
						int size_key, char *value);
char					*find_env_variable_key(char *arg);

int						set_value_and_size_key_lst_status(char **value,
						int *size_key, t_mini *mini);
int						set_value_and_size_key_digit(char **value,
						int *size_key);
int						set_value_and_size_key_quote(char **value,
						int *size_key);
int						set_value_and_size_key_lst_word(char **value,
						int *size_key, t_mini *mini);
int						set_value_and_size_key_default(char *str, char **value,
						int *size_key, t_mini *mini);

int						replace_variable_word(char **word, t_mini *mini);
int						replace_variable_command(t_command *command,
						t_mini *mini);

int						sup_quote_word(char **word);
int						sup_quote_command(t_command *command);

int						actualize_lst_word(t_command *command, t_mini *mini);

int						open_all_redirections(t_command *command,
						t_command *prv_command, t_mini *mini);

void					exec_command_builtin(t_command *command, int *status,
						t_mini *mini);

int						actualize_env_tab(t_mini *mini);
int						actualize_path(t_mini *mini);

int						replace_old_pwd(t_mini *mini);
int						replace_pwd(char *path, t_mini *mini);
int						restore_pwd_and_oldpwd(char *key, t_mini *mini);

int						builtin_cd(t_command *command, t_mini *mini);

int						builtin_echo(t_command *command, t_mini *mini);

int						builtin_env(t_command *command, t_mini *mini);

int						builtin_exit(t_command *command, t_mini *mini);

bool					empty_variable(t_env_var *env_var);
bool					check_key_ok(char *key);
bool					key_not_found(char *key, t_mini *mini);
bool					value_not_found(char *key, t_mini *mini);

char					*get_env_var_value(char *key, t_mini *mini);
int						get_dup_env_var_value(char **str, char *key,
						t_mini *mini);
int						set_env_var_value(char *key, char *new_value,
						t_mini *mini);

int						actualize_variable(char *arg, char *key, t_mini *mini);
int						export_new_variable(char *arg, char *key, t_mini *mini);
int						export(char *arg, char *key, t_mini *mini);
int						manage_export_arg(char *arg, t_mini *mini);
void					display_export(t_command *command, t_mini *mini);

int						builtin_export(t_command *command, t_mini *mini);

int						builtin_pwd(t_command *command, t_mini *mini);

int						compare_env_var(t_env_var *env_var, char *key);
int						builtin_unset(t_command *command, t_mini *mini);

void					exec_command_default(t_command *command, int *status,
						pid_t *pid, t_mini *mini);

bool					is_absolute_path(char *path);
bool					is_relative_path(char *path);
int						check_path_reg_file(char *path);

int						set_fst_arg(t_command *command, t_mini *mini);

void					child_process(t_command *command, t_mini *mini);

int						add_new_process(int status, pid_t pid, t_mini *mini);

void					close_clean(int *fd);
void					clean_redir(void *content);
void					clean_command(void *content);
void					clean_env_var(void *content);
void					clean_mini(t_mini *mini);

void					put_error_msg(int error_code, char *indic1,
						char *indic2);

void					quit(int code, t_mini *mini);

int						get_next_line(int fd, char **line);

#endif
