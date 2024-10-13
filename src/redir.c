/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:54:14 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/13 18:04:30 by vconesa-         ###   ########.fr       */
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

void	handle_herdoc(t_herdoc *hcmd)
{
	int		p[2];
	char	*line;

	if (pipe(p) < 0)
		exit_error("pipe");
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
	close(p[1]);
	if (fork1() == 0)
		exec_pipe_child(hcmd->right, 0, p[0], -1);
	close(p[0]);
	wait(0);
}

void	handle_redir(t_redir *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, PERMISSIONS) < 0)
	{
		printf("open %s failed\n", rcmd->file);
		exit(1);
	}
	runcmd(rcmd->cmd);
}
