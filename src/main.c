/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/13 18:51:11 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	getcmd(char *buff, int nbuf)
{
	char	*input;

	ft_memset(buff, 0, nbuf);
	input = readline(PROMPT);
	if (!input)
		return (-1);
	ft_strlcpy(buff, input, nbuf);
	if (buff[0] == 0)
		return (-1);
	free(input);
	return (0);
}

void	runcmd(t_cmd *cmd)
{
	extern char	**environ;
	t_exec		*ecmd;

	if (cmd == 0)
		exit(1);
	if (cmd->type == EXEC_T)
	{
		ecmd = (t_exec *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		execve(ecmd->argv[0], ecmd->argv, environ);
		printf("exec %s failed\n", ecmd->argv[0]);
	}
	else if (cmd->type == REDIR_T)
		handle_redir((t_redir *)cmd);
	else if (cmd->type == PIPE_T)
		handle_pipe((t_pipe *)cmd);
	else if (cmd->type == HERDOC_T)
		handle_herdoc((t_herdoc *)cmd);
	else
		exit_error("runcmd error");
	exit(0);
}

int	main(void)
{
	static char	buff[100];
	int			fd;

	fd = open(PROMPT, O_RDWR);
	while (fd >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
		fd = open(PROMPT, O_RDWR);
	}
	while ((getcmd(buff, sizeof(buff)) >= 0))
	{
		add_history(buff);
		if (do_builtins(buff))
			continue ;
		if (fork1() == 0)
		{
			runcmd(parsecmd(buff));
		}
		wait(0);
	}
	exit(1);
}
