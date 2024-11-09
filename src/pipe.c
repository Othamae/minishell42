/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:22:06 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/08 18:13:39 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe_child(t_cmd *cmd, int p[2], int is_left, t_context *context)
{
	if (is_left)
	{
		close(1);
		dup(p[1]);
	}
	else
	{
		close(0);
		dup(p[0]);
	}
	close(p[0]);
	close(p[1]);
	runcmd(cmd, context);
}

int	handle_pipe(t_pipe *pcmd, t_context *context)
{
	int	p[2];
	int	status_left;
	int	status_right;

	status_left = 0;
	status_right = 0;
	if (pipe(p) < 0)
		exit_error("pipe");
	if (fork1() == 0)
		exec_pipe_child(pcmd->left, p, 1, context);
	if (fork1() == 0)
		exec_pipe_child(pcmd->right, p, 0, context);
	close(p[0]);
	close(p[1]);
	wait(&status_left);
	wait(&status_right);
	status_left = WEXITSTATUS(status_left);
	status_right = WEXITSTATUS(status_right);
	return (status_right);
}
