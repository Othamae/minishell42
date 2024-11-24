/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/24 14:07:42 by vconesa-         ###   ########.fr       */
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

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6));
}

void	handle_exec_t(t_exec *cmd, t_context *context)
{
	int	status;

	if (is_builtin(cmd->argv[0]))
		context->last_status = handle_builtins(cmd->argv, context);
	else
	{
		if (fork1() == 0)
			exit(handle_exec(cmd, context));
		wait(&status);
		context->last_status = WEXITSTATUS(status);
	}
}

void	runcmd(t_cmd *cmd, t_context *context)
{
	int	status;

	if (cmd == 0)
		return ;
	status = 0;
	if (cmd->type == EXEC_T)
		handle_exec_t((t_exec *)cmd, context);
	else if (cmd->type == REDIR_T)
		handle_redir((t_redir *)cmd, context);
	else if (cmd->type == PIPE_T)
		handle_pipe((t_pipe *)cmd, context);
	else if (cmd->type == HERDOC_T)
		handle_herdoc((t_herdoc *)cmd, context);
	else if (cmd->type == AND_T || cmd->type == OR_T)
		handle_and_or((t_clist *)cmd, &status, context);
	else if (cmd->type == SUBSHELL_T)
		handle_subshell((t_subshell *)cmd, &status, context);
	else
		exit_error("runcmd error");
	if (context->is_pipe_child)
		exit(context->last_status);
}

int	main(void)
{
	static char	buff[MAX_BUFFER_SIZE];
	t_context	context;
	t_cmd		*cmd;
	t_wildbuff	buf;

	buf.buffer = NULL;
	context.last_status = 0;
	context.is_pipe_child = 0;
	context.redir_handled = 0;
	handle_signals();
	while ((getcmd(buff, sizeof(buff)) >= 0))
	{
		add_history(buff);
		cmd = parsecmd(buff, &buf);
		if (cmd)
			runcmd(cmd, &context);
		free_cmd(cmd);
		if (buf.buffer)
			free(buf.buffer);
	}
	exit(1);
}
