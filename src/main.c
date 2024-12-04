/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/04 10:36:22 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_received = 0;

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

void	handle_signal_exit_status(t_exec *cmd, int status, t_context *context)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			if (ft_strncmp(cmd->argv[0], "cat", 4) == 0)
			{
				write(1, "\n", 1);
				context->last_status = 130;
			}
			else
				context->last_status = 128 + WTERMSIG(status);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			if (ft_strncmp(cmd->argv[0], "cat", 4) == 0)
			{
				write(1, "\n", 1);
				context->last_status = 131;
			}
			else
				context->last_status = 128 + WTERMSIG(status);
		}
	}
	else
		context->last_status = WEXITSTATUS(status);
}

void	handle_exec_t(t_exec *cmd, t_context *cont)
{
	int	status;

	if (is_builtin(cmd->argv[0]))
		cont->last_status = handle_builtins(cmd->argv, cont, (t_cmd *)cmd);
	else
	{
		if (fork1() == 0)
		{
			default_signals();
			exit(handle_exec(cmd, cont));
		}
		ignore_signals();
		wait(&status);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		handle_signal_exit_status(cmd, status, cont);
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
		handle_and_or((t_clist *)cmd, context);
	else if (cmd->type == SUBSHELL_T)
		handle_subshell((t_subshell *)cmd, &status, context);
	else
		exit_error("runcmd error");
	if (context->is_pipe_child)
		exit(context->last_status);
}

int	main(int argc, char **argv, char **env)
{
	static char	buff[MAX_BUFFER_SIZE];
	t_context	context;
	t_cmd		*cmd;
	t_wildbuff	buf;

	init_buff(&buf, argc, argv);
	init_context(env, &context);
	handle_signals();
	while ((getcmd(buff, sizeof(buff)) >= 0))
	{
		check_sigint(&context);
		add_history(buff);
		cmd = parsecmd(buff, &buf);
		if (cmd)
			runcmd(cmd, &context);
		free_cmd(cmd);
		cmd = NULL;
		if (buf.buffer)
			free(buf.buffer);
		buf.buffer = NULL;
	}
	if (context.env)
		free_env(&context);
	exit(1);
}
