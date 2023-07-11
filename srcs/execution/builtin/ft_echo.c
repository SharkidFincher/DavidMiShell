/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:29:47 by svoi              #+#    #+#             */
/*   Updated: 2023/07/10 11:22:03 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_echo_with_n(t_cmd_lst *cmd_lst)
{
	char	*str;

	str = cmd_lst->cmd_node->argument[1];
	if (str && ft_strncmp(str, "-n", 2) == 0)
		return (true);
	return (false);
	/*
	return (cmd_lst->cmd_node->argument[0] && ft_strncmp(cmd_lst->cmd_node->argument[0], "echo", 4) == 0
		&& cmd_lst->cmd_node->argument[1] && ft_strncmp(cmd_lst->cmd_node->argument[1], "-n", 2) == 0);
	*/
}

int	ft_echo(t_data *data, t_cmd_lst *cmd_lst)
{
	bool	n_option;
	int		i;

	printf("\t..ft_echo\n");
	n_option = ft_echo_with_n(cmd_lst);
	i = 0;
	if (n_option)
		i = 2;
	else
		i = 1;
	while (cmd_lst->cmd_node->argument[i])
	{
		ft_putstr_fd(cmd_lst->cmd_node->argument[i], 1);
		if (cmd_lst->cmd_node->argument[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	data->exit_return = 0;
	/* DEBUG */
	//printf("\t..ft_echo\t exit_return:[%d]\n", data->exit_return);
	/* ***** */
	return 0;
}