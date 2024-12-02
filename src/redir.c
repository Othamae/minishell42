/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:54:14 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/01 19:35:06 by vconesa-         ###   ########.fr       */
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

static void	process_herdoc(char	*line, t_herdoc *hcmd, int p[2]
	, t_context *context)
{
	signal(SIGINT, handle_sigint_herdoc);
	while (1)
	{
		if (g_signal_received == SIGINT)
			exit(context->last_status = 130);
		line = readline("> ");
		if (!line || g_signal_received == SIGINT)
		{
			context->last_status = 130;
			break ;
		}
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
	signal(SIGINT, SIG_DFL);
}

void	handle_last_status(t_context *context)
{
	if (WIFEXITED(context->last_status))
		context->last_status = WEXITSTATUS(context->last_status);
	else if (WIFSIGNALED(context->last_status))
		context->last_status = 128 + WTERMSIG(context->last_status);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	handle_herdoc(t_herdoc *hcmd, t_context *context)
{
	int		p[2];
	char	*line;

	line = NULL;
	if (pipe(p) < 0)
		exit_error("pipe");
	if (fork1() == 0)
	{
		default_signals();
		process_herdoc(line, hcmd, p, context);
		close(p[1]);
		if (fork1() == 0)
		{
			exec_pipe_child(hcmd->right, p, 0, context);
			exit(context->last_status);
		}
		ignore_signals();
		wait(&context->last_status);
		handle_signals();
		exit(WEXITSTATUS(context->last_status));
	}
	close(p[1]);
	ignore_signals();
	wait(&context->last_status);
	handle_last_status(context);
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
