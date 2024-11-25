/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:26:11 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/25 19:21:18 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_exec(t_cmd *cmd)
{
	int		i;
	t_exec	*exec_cmd;

	exec_cmd = (t_exec *)cmd;
	i = 0;
	while (i < MAXARGS && exec_cmd->argv[i])
	{
		exec_cmd->argv[i] = NULL;
		i++;
	}
	i = 0;
	while (i < MAXARGS && exec_cmd->eargv[i])
	{
		exec_cmd->eargv[i] = NULL;
		i++;
	}
}

static void	free_redir(t_cmd *cmd)
{
	t_redir		*redir_cmd;
	t_herdoc	*herdoc_cmd;

	if (cmd->type == REDIR_T)
	{
		redir_cmd = (t_redir *)cmd;
		redir_cmd->file = NULL;
		redir_cmd->efile = NULL;
		free_cmd(redir_cmd->cmd);
	}
	else if (cmd->type == HERDOC_T)
	{
		herdoc_cmd = (t_herdoc *)cmd;
		free(herdoc_cmd->delim);
		free_cmd(herdoc_cmd->right);
	}
}

static void	free_pipe(t_cmd *cmd)
{
	t_pipe	*pipe_cmd;

	pipe_cmd = (t_pipe *)cmd;
	free_cmd(pipe_cmd->left);
	free_cmd(pipe_cmd->right);
}

static void	free_andor(t_cmd *cmd)
{
	t_clist		*clist_cmd;
	t_subshell	*subshell_cmd;

	if (cmd->type == AND_T || cmd->type == OR_T)
	{
		clist_cmd = (t_clist *)cmd;
		free_cmd(clist_cmd->left);
		free_cmd(clist_cmd->right);
	}
	else if (cmd->type == SUBSHELL_T)
	{
		subshell_cmd = (t_subshell *)cmd;
		free_cmd(subshell_cmd->subcmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC_T)
		free_exec(cmd);
	else if (cmd->type == REDIR_T || cmd->type == HERDOC_T)
		free_redir(cmd);
	else if (cmd->type == PIPE_T)
		free_pipe(cmd);
	else if (cmd->type == AND_T || cmd->type == OR_T || cmd->type == SUBSHELL_T)
		free_andor(cmd);
	free(cmd);
}
