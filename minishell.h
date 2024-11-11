/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:54:01 by zayaz             #+#    #+#             */
/*   Updated: 2024/11/08 17:59:32 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "includes/libft/libft.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/readline.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define IN_CAT 1
# define IN_HERADOC 2
# define IN_PARENT 3

int					g_global_signal;

typedef struct s_mlist
{
	void			*content;
	struct s_mlist	*next;
	void			*key;

}					t_mlist;

typedef enum set_meta
{
	Tilde = 4,
	Dolar = 5,
	S_Dolar = 6,
	Redirect = 7,
}					t_set_meta;

typedef struct s_lexer
{
	char			*cmd;
	int				key;
}					t_lexer;
typedef struct s_process
{
	pid_t			pid;
	int				fd[2];
}					t_process;
typedef struct s_program
{
	t_mlist			*envp_list;
	t_mlist			*export_list;
	char			*input;
	t_lexer			***parser_input;
	int				export_flag;
	int				check_quote;
	int				control_q_split;
	int				control_p_split;
	int				unset_flag;
	t_process		*process;
	int				p_count;
	char			redi_type;
	char			**env_cmd;
	char			**sep_path;
	char			**cmd;
	int				fd_input;
	int				fd_output;
	int				status;
	int				*hd_flag;
	int				*here_fd;
	int				redi_flag;
	int				rdr_error;
	int				built_check;
	int				finish_check;
	int				start_cmd;
	int				flag_identifier;

}					t_program;
void				ft_init_program(t_program *program, char **envp);
int					ft_parser(t_program *program, char *input);
int					p_quote(t_program *program, char *input);
int					p_pipe(t_program *program, char *input);
int					p_redirection(t_program *program, char *input);
char				**zi_split(t_program *program, char *s, char c,
						int is_space);
char				*walk_string(t_program *program, char *s, char c,
						int is_space);
int					zi_count_string(char *s, char c);
int					set_meta(char *meta);
int					zi_strrchr(const char *s, int c, int i);
void				run_dolar(t_program *program);
char				*zi_strlcpy(char *dst, const char *src, size_t dstsize);
char				*in_quote_string(char *s, char c);
size_t				zi_strlen(char *s, char c, int dhand);
char				*dolar_env(t_program *program, char *parser_input);
void				dolar_free(char *env_str, char *after_dolar);
void				dolar_handler(t_program *program, t_lexer *parser_input);
char				*env_count_str(t_lexer *parser_input, int *i);
char				*del_quote(char *dst, char *src, size_t dstsize);
void				signal_init(void);
void				heredoc_main(t_program *program);
int					zi_redirectchr(const char *s, char c);
int					heredoc_count(t_program *program);
void				equal_in_export(t_program *program, char **cmd, int *i);
int					zi_strcmp(const char *s1, const char *s2);
void				quote_skip(char *cmd, int *z);
char				*search_env(char *key, t_mlist *envpx_lst);
void				zi_exec(t_program *program);
void				exec_cmd(t_program *program, int *i);
void				run_input(t_program *program, char *s);
void				run_output(t_program *program, char *s);
void				append_output(t_program *program, char *s);
void				relative_path(t_program *program);
void				pipe_dup(t_program *program, int *i);
void				find_path(t_program *program);
void				fill_env_cmd(t_program *program);
int					is_builtin(t_program *program);
void				echo(t_program *program, char **cmd);
void				pwd(t_program *program);
void				cd(t_program *program, char **cmd);
void				env(t_program *program, char **cmd);
void				export(t_program *program, char **cmd);
void				zi_unset(t_program *program, char **cmd);
void				search_set_env(t_program *program, char *key, char *content,
						t_mlist *envpx_list);
int					check_identifier(char *parser_input);
void				redirect(t_program *program, int *i);
int					redirect_c(t_program *program, int *i);
int					pipe_count(t_program *program);
void				main_builtin(t_program *program);
void				child_builtin(t_program *program);
void				close_pipe(t_program *program);
void				ft_exit(t_program *program);
void				exit_code_handler(t_program *program);
int					is_close_quote(char *str, size_t i, char q_type);
char				*expand_dollar_variables(t_program *program, int *i,
						t_lexer *parser_input);
int					is_single_dollar(char *cmd);
char				*dollar_join(char *env_str, char *before_cmd,
						char *after_dolar, char *tmp);
char				*set_expand_dollar_variables(t_program *program,
						t_lexer *parser_input, int *i, char *env_str);
int					error_message(char *str);
void				exec_error(t_program *program, char *s, int exit_code);
void				free_array(char **tmp);
void				free_program(t_program *program);
void				free_parser_input(t_program *program);
int					p_error(t_program *program, char *str);
int					rdr_take_status(t_program *program, int pid);
void				file_error(t_program *program);
void				find_dollar_in_quotes(char *s, char q_type, int *i);
void				handle_unset_identifier(t_program *program, char **cmd,
						int *i);
int					zi_strchr(const char *s, int c, char type);
void				build_error(t_program *program, char *cmd, char *message);
void				identifier_error(t_program *program, char *cmd, char *s,
						char *message);
void				search_del_env(t_program *program, char *key,
						t_mlist **lst);
void				exit_error(char *cmd, char *s, char *message);
int					check_key(char *key, t_mlist *envpx_lst);
void				run_one_cmd(t_program *program, int *i);
void				fillable_count(char *cmd, int *z, int *count);
void				redi_skip(t_lexer **parser_input, int *z, int *j);
void				exec_command(t_program *program);
void				find_loc(char *cmd, int *z);
char				*take_redi_doc(t_program *program, int *i, int *j, int *z);
void				parent_heredoc(t_program *program, t_process hd_process);
void				handle_heredoc_redirect(t_program *program,
						void run_redirect(t_program *, char *), char *doc);
char				*before_dolar(t_lexer *parser_input, int *i, int is_in);
t_mlist				*zi_lstnew(void *content, char *key);
void				zi_lstadd_back(t_mlist **lst, t_mlist *new);
t_mlist				*zi_lstlast(t_mlist *lst);
int					zi_lstsize(t_mlist *lst);
void				free_path(t_program *program);
void				cd_helper(t_program *program);
void				cd_add_list(t_program *program, char *key, char *content);

#endif