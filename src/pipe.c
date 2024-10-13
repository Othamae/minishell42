/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:22:06 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/13 18:49:31 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe_child(t_cmd *cmd, int p[2], int is_left)
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
	runcmd(cmd);
}

void	handle_pipe(t_pipe *pcmd)
{
	int	p[2];

	if (pipe(p) < 0)
		exit_error("pipe");
	if (fork1() == 0)
		exec_pipe_child(pcmd->left, p, 1);
	if (fork1() == 0)
		exec_pipe_child(pcmd->right, p, 0);
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}
