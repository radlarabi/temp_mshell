/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:11:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/19 17:08:02 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <wait.h>

# define WORD 1
# define DASH 2
# define SPACES 3
# define DOUBLE_Q 4
# define SINGLE_Q 5
# define RED_IN 6
# define RED_OUT 7
# define HERDOC 8
# define APPE 9
# define PIPE 10
# define ENV 11
# define S_DOTS 12
# define D_DOTS 13
# define OPER 14
# define N_OPER 15
# define QEST 16
# define OTHER 17
# define AND 17
# define ERROR_MSG "\033[0;31m syntax error \033[0m"
# define MINISHELL "\033[0;32m minishell -> \033[0m"

# define GENERAL 1
# define IN_DC 2
# define IN_SC 3


typedef struct s_env
{
	char				*value;
	char				*var;
	struct s_env		*next;
}						t_env;

typedef	struct s_gv
{
	t_env *env;
	int	exit_status;
}						t_globalv;

static t_globalv	*g_globalv;

typedef struct s_cmd
{
	char				*content;
	int					type;
	int					state;
	int					opr;
	int					len;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_command;

typedef struct s_cmd_line1
{
	int		num_cmds;
	int		num_pipes;
	char	**av;
	char	**ev;
	char	**cmds;
	char	**path;
}			t_cmd_line1;

typedef struct s_cmd_line
{
	int					infile;
	int					outfile;
	char 				*here_f;
	char 				*str_cmd;
	int					index;
	char				*fd_error;
	char				**cmds;
	struct s_cmd_line	*next;
}						t_cmd_line;



/*  fonction builtins  */
int						ft_pwd(t_cmd_line **commands_v);
int						ft_echo(t_cmd_line **commands_v);
int						ft_cd(t_cmd_line **cd_cmd);
/* end */

void ft_execution(t_cmd_line *cmd_l);


void					error_msg(void);
t_command	*init_cmd(t_command	*cmd);
void					ft_lstadd_back(t_command **lst, t_command *new);
void					ft_lstadd_back_cmds(t_cmd_line **lst, t_cmd_line *new);
void					displayList(t_command **node);
int						check_syntax(t_command **cmd);
void					set_states(t_command **cmd);
t_cmd_line				*commands_struct(char **cmds);
int						files_here_doc(char **temp, t_cmd_line **tmp, int *j,int flag);
int						files_red_in(char **temp, t_cmd_line **tmp, int *j);
int						files_red_out(char **temp, t_cmd_line **tmp, int *j);
int						files_append(char **temp, t_cmd_line **tmp, int *j);
char					*change_quote_in_files(char *str);
char					*get_stop_heredoc(char *str);
int						fill_content_heredoc(char *stop, int fd);
int						sub_check_qotes(char *str, int *i, int a);
int						check_close_qotes(char *str);
void					fill_types(t_command *tmp, char c, int *i, char *str);
char					*struct_to_str(t_command **cmd);
void					ft_lstadd_middle(t_command **cmd);
void					display_pipe(t_cmd_line *cmd_l);
char *get_path_command(char **path, char *cmd);
// int						count_pipes(t_command **cmd);
t_cmd_line				*lst_init_cmds();
void					extend_cmd(t_command **cmd);
char					*ft_join_char(char *str, char c);
void					skip_and_fill_in_quotes(char *str, char **s, int a,
							int *i);
void					skip_in_quotes(char *str, int a, int *i);
char					*set_spliter(char *str, char c);
char					**splite_with_pipes(t_command **cmd);
char					**splite_with_space(char *str);
t_env *get_env(char **ev);
char *ft_getenv(char *str);
int is_quots(char *str,int index);
char *extand_variable(char *cmds);
void    execution(t_cmd_line *cmd);

char **get_path(t_env *env);
void	pipex(t_cmd_line1 *cmd,t_cmd_line *cmd_l);
#endif
