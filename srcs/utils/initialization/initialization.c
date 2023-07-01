/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:15:20 by sbocanci          #+#    #+#             */
/*   Updated: 2023/06/29 17:33:29 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_data *data)
{
	int		count;

	data->m_envp = (char **)malloc(sizeof(char*) * BUFFER);
	if (!data->m_envp)
		return ;
	count = 0;
	while (data->env[count])
	{
		data->m_envp[count] = ft_strdup(data->env[count]);
		count++;
	}
	while (count < BUFFER)
		data->m_envp[count++] = NULL;
}

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->m_envp = NULL;
	init_envp(data);
	// check if the is a malloc error for m_envp
	data->nodes = NULL;
}