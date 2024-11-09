/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 11:34:37 by vconesa-         ###   ########.fr       */
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
	if (input[0] == 0)
	{
		free(input);
		return (0);
	}
	ft_strlcpy(buff, input, nbuf);
	if (buff[0] == 0)
		return (-1);
	free(input);
	return (0);
}

void	runcmd(t_cmd *cmd, t_context *context)
{
	int	status;

	if (cmd == 0)
		exit(1);
	status = 0;
	if (cmd->type == EXEC_T)
		status = handle_exec((t_exec *)cmd, context);
	else if (cmd->type == REDIR_T)
		handle_redir((t_redir *)cmd, context);
	else if (cmd->type == PIPE_T)
	{
		status = handle_pipe((t_pipe *)cmd, context);
		exit(status);
	}
	else if (cmd->type == HERDOC_T)
		handle_herdoc((t_herdoc *)cmd, context);
	else if (cmd->type == AND_T || cmd->type == OR_T)
		handle_and_or((t_clist *)cmd, &status, context);
	else if (cmd->type == SUBSHELL_T)
		handle_subshell((t_subshell *)cmd, &status, context);
	else
		exit_error("runcmd error");
	context->last_status = WEXITSTATUS(status);
	exit(context->last_status);
}

static void	initialize_fd(void)
{
	int	fd;

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
}

int	main(void)
{
	static char	buff[100];
	t_context	context;

	context.last_status = 0;
	initialize_fd();
	handle_signals();
	while ((getcmd(buff, sizeof(buff)) >= 0))
	{
		add_history(buff);
		if (do_builtins(buff))
			continue ;
		if (fork1() == 0)
			runcmd(parsecmd(buff), &context);
		wait(&context.last_status);
		context.last_status = WEXITSTATUS(context.last_status);
	}
	exit(1);
}
