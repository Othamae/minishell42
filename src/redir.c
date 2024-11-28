/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:54:14 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/28 14:56:25 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_write_error(char *line, int fd)
{
	printf("write");
	free(line);
	close(fd);
	exit(EXIT_FAILURE);
}

static void	process_herdoc(char	*line, t_herdoc *hcmd, int p[2])
{
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, hcmd->delim, ft_strlen(hcmd->delim)) == 0)
		{
			free(line);
			break ;
		}
		if (write(p[1], line, ft_strlen(line)) != (ssize_t)ft_strlen(line)
			|| write(p[1], "\n", 1) != 1)
			handle_write_error(line, p[1]);
		free(line);
	}
}

void	handle_herdoc(t_herdoc *hcmd, t_context *context)
{
	int		p[2];
	char	*line;

	line = NULL;
	if (pipe(p) < 0)
		exit_error("pipe");
	process_herdoc(line, hcmd, p);
	close(p[1]);
	if (fork1() == 0)
	{
		default_signals();
		exec_pipe_child(hcmd->right, p, 0, context);
	}
	ignore_signals();
	wait(0);
}

void	handle_redir(t_redir *rcmd, t_context *context)
{
	if (fork1() == 0)
	{
		default_signals();
		close(rcmd->info.fd);
		if (open(rcmd->file, rcmd->info.mode, PERMISSIONS) < 0)
		{
			printf("open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd, context);
		exit(context->last_status);
	}
	ignore_signals();
	wait(&context->last_status);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
