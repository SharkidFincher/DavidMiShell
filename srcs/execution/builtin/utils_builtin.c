/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:30:20 by svoi              #+#    #+#             */
/*   Updated: 2023/07/13 13:41:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_cmd_lst *cmd_lst)
{
	char	**argument;
	int		builtin;

	argument = cmd_lst->cmd_node->argument;
	builtin = N_A;
	if (argument)
	{
		if (ft_strncmp(argument[0], "cd", 2) == 0)
			builtin = CD;
		else if (ft_strncmp(argument[0], "echo", 4) == 0)
			builtin = ECHO;
		else if (ft_strncmp(argument[0], "env", 3) == 0)
			builtin = ENV;
		else if (ft_strncmp(argument[0], "exit", 4) == 0)
			builtin = EXIT;
		else if (ft_strncmp(argument[0], "export", 6) == 0)
			builtin = EXPORT;
		else if (ft_strncmp(argument[0], "pwd", 3) == 0)
			builtin = PWD;
		else if (ft_strncmp(argument[0], "unset", 5) == 0)
			builtin = UNSET;
	}
	return (builtin);
}

void	exec_builtin(t_data *data, t_cmd_lst *cmd_lst, int builtin)
{
	expand_envp(data, cmd_lst->cmd_node);
	if (builtin == CD)
		ft_cd(data, cmd_lst);
	else if (builtin == ECHO)
		ft_echo(data, cmd_lst);
	else if (builtin == ENV)
		ft_env(data);
	else if (builtin == EXIT)
		ft_exit(data, cmd_lst);
	else if (builtin == EXPORT)
		ft_export(data, cmd_lst);
	else if (builtin == PWD)
		ft_pwd(data);
	else if (builtin == UNSET)
		ft_unset(data, cmd_lst);
}

void	change_pwd(char **m_envp, char *key)
{	
	char	*get_cwd;
	int		i;

	i = 0;
	while (m_envp[i])
	{
		if (ft_strncmp(m_envp[i], key, ft_strlen(key)) == 0)
			break ;
		i++;
	}
	get_cwd = getcwd(NULL, 0);
	if (m_envp[i])
		free(m_envp[i]);
	m_envp[i] = ft_strjoin(key, get_cwd);
	free(get_cwd);
}

/* this adds new key=value pair to the data->m_envp. 
** also appends VALUE to VAR if 'export VAR+=VALUE' is used.
New VAR is created if 'VAR+=' as in bash */
void	add_envp_variable(t_data *data, char *key, char *value, bool append)
{
	int		i;
	char	*new_var;

	new_var = ft_strjoin(key, value);
	if (!new_var)
		return ;
	i = -1;
	while (data->m_envp[++i])
	{
		if (ft_strncmp(data->m_envp[i], key, ft_strlen(key)) == 0)
		{
			if (append)
			{
				free(new_var);
				new_var = ft_strjoin(data->m_envp[i], value);
			}
			free(data->m_envp[i]);
			data->m_envp[i] = new_var;
			return ;
		}
	}
	if (i < BUFFER - 1)
		data->m_envp[i] = new_var;
	else
		free(new_var);
}

/* modified version of strchr(), returns index of first occurance of c */
int	ft_strchr_i(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
