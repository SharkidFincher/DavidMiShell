/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/16 15:55:58 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

void	prompt(t_data *data)
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;
	char		*buffer;
	int			err;
	//int			flag;

	buffer = NULL;
	cmd_lst = NULL;
	token = NULL;
	err = 0;
	//flag = SUCCESS;
	while (!err)
	{
		buffer = readline("DavidMishell: ");
		if (!buffer)
			break ;
		else if (empty_buffer(buffer))
			continue ;
		else
		{
			if (lexing(&token, buffer) == SUCCESS)
				if (check_syntax(&token) == SUCCESS)
					parsing(&cmd_lst, &token);
			if (cmd_lst)
			{
				data->cmd_lst = cmd_lst;
				//print_cmd_lst(&cmd_lst);
				execution(data);
			}
			list_destroy(cmd_lst);
			cmd_lst = NULL;
		}
		if (token)
			printf("test");
		add_history(buffer);
		free(buffer);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		code;

	(void)argv;
	if (argc != 1)
		return (0);
	init_data(&data, env);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt(&data);
	code = data.exit_code;
	if (data.env)
		free_tab(data.env);
	free_tab(data.m_envp);
	free_tab(data.path_dirs);
	list_destroy(data.cmd_lst);
	printf("exit\n");
	return (code);
}
