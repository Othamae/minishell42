/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:22:06 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/28 14:42:13 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe_child(t_cmd *cmd, int p[2], int is_left, t_context *context)
{
	if (is_left)
	{
		close(1);
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		context->is_pipe_child = 1;
		runcmd(cmd, context);
		exit(context->last_status);
	}
	else
	{
		close(0);
		dup2(p[0], STDIN_FILENO);
		close(p[1]);
		close(p[0]);
		context->is_pipe_child = 1;
		runcmd(cmd, context);
		exit(context->last_status);
	}
}

void	handle_pipe(t_pipe *cmd, t_context *context)
{
	int	p[2];
	int	status_left;
	int	status_right;

	if (pipe(p) < 0)
		exit_error("pipe failed");
	if (fork1() == 0)
	{
		default_signals();
		exec_pipe_child(cmd->left, p, 1, context);
	}
	if (fork1() == 0)
	{
		default_signals();
		exec_pipe_child(cmd->right, p, 0, context);
	}
	close(p[0]);
	close(p[1]);
	ignore_signals();
	wait(&status_left);
	context->last_status = WEXITSTATUS(status_left);
	context->is_pipe_child = 0;
	wait(&status_right);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
