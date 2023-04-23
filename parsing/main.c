/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/19 16:58:56 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_list(t_command **cmd)
{
	t_command *temp;
	temp = *cmd;
	t_command *content;
	while (temp->next)
	{
		content = temp;
		free(content->content);
		free(content);
		temp = temp->next;
	}
	*cmd = NULL;
}
void	ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
	{
		*lst = new;
	}
	else
	{
		temp->next = new;
		new->prev = temp;
	}
	//free_list(&new);
}
void	ft_lstadd_back_cmds(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
	{
		*lst = new;
	}
	else
	{
		temp->next = new;
	}
}
void	displayList(t_command **node)
{
	while ((*node) != NULL)
	{
		printf("%s -> %d -> %d\n", (*node)->content, (*node)->type,
				(*node)->state);
		(*node) = (*node)->next;
	}
	printf("\n");
}

int	sub_check_qotes(char *str, int *i, int a)
{
	int	j;

	j = 0;
	if (str[*i] == a)
	{
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == a)
			{
				j = 1;
				break ;
			}
			(*i)++;
		}
		if (j == 0)
			return (0);
	}
	return (1);
}

int	check_close_qotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!sub_check_qotes(str, &i, 39) || !sub_check_qotes(str, &i, 34))
		{
			//free(str);
			error_msg();
			return (0);
		}
		i++;
	}
	return (1);
}

char	*struct_to_str(t_command **cmd)
{
	t_command	*tmp;
	char		*str;

	tmp = *cmd;
	str = NULL;
	while (tmp != NULL)
	{
		str = ft_strjoin(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

void	ft_lstadd_middle(t_command **cmd)
{
	t_command	*new;
	t_command	*new1;

	new = init_cmd(new);
	new->content = " ";
	new->type = SPACES;
	new->state = GENERAL;
	new->len = 1;
	new1 = init_cmd(new1);
	new1->state = GENERAL;
	new1->content = " ";
	new1->type = SPACES;
	new1->len = 1;
	new->next = (*cmd)->next;
	new->prev = (*cmd);
	(*cmd)->next = new;
	//free_list(&new);
	/*hada code dyal espace befor node*/
	if ((*cmd)->prev != NULL)
	{
		new1->prev = (*cmd)->prev;
		new1->next = (*cmd);
		(*cmd)->prev->next = new1;
		(*cmd)->prev = new1;
		//free_list(&new1);
	}
	else
	{
		new1->prev = NULL;
		new1->next = (*cmd);
		(*cmd)->prev = new1;
		//free_list(&new1);
	}
	/*end*/
}

void	display_pipe(t_cmd_line *cmd_l)
{
	int i = 0;
	while(cmd_l)
	{
		i = 0;
		while(cmd_l && cmd_l->cmds[i])
		{
			printf("cmds[%d] %s\n", i, cmd_l->cmds[i]);
			i++;
		}
		cmd_l = cmd_l->next;
	}
}
// int 	count_pipes(t_command **cmd)
// {
// 	t_command *tmp;
// 	int count;

// 	count = 0;
// 	tmp = *cmd;
// 	while(tmp)
// 	{
// 		if (tmp->type == PIPE && tmp->state == GENERAL)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return count;
// }


void	extend_cmd(t_command **cmd)
{
	t_command	*tmp;
	t_command	*node;
	int			i;

	i = 0;
	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp->state == GENERAL && (tmp->type == RED_IN
			|| tmp->type == RED_OUT || tmp->type == PIPE
			|| tmp->type == HERDOC || tmp->type == APPE))
		{
			ft_lstadd_middle(&tmp);
		}
		tmp = tmp->next;
		i++;
	}
}


char *ft_getenv(char *str)
{
	t_env *temp;
	char *tmp;
	tmp = ft_strdup("");
	temp = g_globalv->env;
	while(temp)
	{
		if (!ft_strcmp(str, temp->var))
			return temp->value;
		temp = temp->next;
	}
	return (tmp);
}

int is_quots(char *str,int index)
{
	int i;
	i = 0;
	int open;
	open = 0;
	while (str[i] && i != index)
	{
		if (!open && str[i] == '\"')
			open = 2;
		else if (open == 2 && str[i] == '\"')
			open = 0;
		if (!open && str[i] == '\'')
			open = 3;
		else if (open == 3 && str[i] == '\'')
			open = 0;
		i++;
	}
	return open;
}
static void	free_2d_table(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	main_free(t_command **cmd, t_cmd_line **cmd_l)
{
	t_command *tmp;
	t_cmd_line *tmp1;
	tmp = *cmd;
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
	tmp1 = *cmd_l;
	while(tmp1)
	{
		if (tmp1->fd_error)
			free(tmp1->fd_error);
		tmp1 = tmp1->next;
	}
}
char	*search_path(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], "PATH", 4))
			return (ev[i]);
		i++;
	}
	return (NULL);
}
char	**get_path_a(char **ev)
{
	int		i;
	char	**path;
	char	**temp;
	char *a;

	temp = ft_split(search_path(ev), '=');
	path = ft_split(temp[1], ':');
	// free_2d_table(temp);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}
t_cmd_line1	*nodes_to_struct(t_cmd_line *cmd_l, char **ev)
{
	t_cmd_line1 *cmd_l1;
	int i = 0;
	cmd_l1 = malloc(sizeof(t_cmd_line1));
	cmd_l1->cmds = malloc(sizeof(char *) * 5); //5 is temp , and it should be the size of the cmd_l !
	while(cmd_l)
	{
		cmd_l1->cmds[i] = ft_strdup(cmd_l->str_cmd);
		// printf("--> %s\n",cmd_l1->cmds[i]);
		i++;
		cmd_l = cmd_l->next;
	}
	cmd_l1->num_cmds = i;
	cmd_l1->num_pipes = i - 1;
	if (cmd_l1->num_pipes < 0)
		cmd_l1->num_pipes = 0;
	cmd_l1->cmds[i] = 0;
	cmd_l1->path = get_path(g_globalv->env);
	cmd_l1->ev = ev;

	return cmd_l1;
}
int	main(int ac, char **av, char **env)
{
	char		*str;
	int			i;
	pid_t id;
	int status;
	int			len;
	t_command	*cmd = NULL;
	t_command	*node;
	t_command	*tmp;
	t_command	*tmp_1;
	t_cmd_line *cmd_l;
	t_cmd_line1 *cmd_l1;
	char **temp;
	g_globalv = malloc(sizeof(g_globalv));
	g_globalv->env = get_env(env);
	while (1)
	{
		i = 0;
		str = readline(MINISHELL);
		add_history(str);
		while (str[i])
		{
			tmp = init_cmd(tmp);
			fill_types(tmp, str[i], &i, str);
			tmp->content = ft_substr(str, i - tmp->len, tmp->len);
			ft_lstadd_back(&cmd, tmp);
			//free_list(&tmp);
			//tmp = NULL;
		}
		if (!check_close_qotes(str))
		{
			//free_list(&cmd);
			cmd = NULL;
			continue ;
		}
		set_states(&cmd);
		if (!check_syntax(&cmd))
		{
			//free_list(&cmd);
			cmd  = NULL;
			continue ;
		}
		// exit(0);
		temp = splite_with_pipes(&cmd);
		cmd_l = commands_struct(temp);
		cmd_l1 = nodes_to_struct(cmd_l, env);
		pipex(cmd_l1, cmd_l);
	//	free_2d_table(temp);

		// display_pipe(cmd_l);
		// displayList(&cmd);
		// execution(cmd_l);
        free(str);
		cmd_l = NULL;
		cmd_l1 = NULL;
		cmd = NULL;
	}
	return (0);
}

