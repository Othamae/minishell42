/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:22:06 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:00 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe_child(t_cmd *cmd, int fd, int fd_in, int fd_out)
{
	close(fd);
	dup(fd_in);
	close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	runcmd(cmd);
}

void	handle_pipe(t_pipe *pcmd)
{
	int	p[2];

	if (pipe(p) < 0)
		exit_error("pipe");
	if (fork1() == 0)
		exec_pipe_child(pcmd->left, 1, p[0], p[1]);
	if (fork1() == 0)
		exec_pipe_child(pcmd->right, 0, p[1], p[0]);
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}
