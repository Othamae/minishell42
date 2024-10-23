/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:32:44 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/23 20:18:12 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_nul_exec(t_cmd *cmd)
{
	t_exec	*ecmd;
	int		i;

	ecmd = (t_exec *)cmd;
	i = 0;
	while (ecmd->argv[i])
	{
		*ecmd->eargv[i] = 0;
		i++;
	}
}

static void	handle_nul_redir(t_cmd *cmd)
{
	t_redir	*rcmd;

	rcmd = (t_redir *)cmd;
	nulterminate(rcmd->cmd);
	*rcmd->efile = 0;
}

static void	handle_nul_pipe(t_cmd *cmd)
{
	t_pipe	*pcmd;

	pcmd = (t_pipe *)cmd;
	nulterminate(pcmd->left);
	nulterminate(pcmd->right);
}

static void	handle_nul_herdoc(t_cmd *cmd)
{
	t_herdoc	*hcmd;

	hcmd = (t_herdoc *)cmd;
	nulterminate(hcmd->right);
}

t_cmd	*nulterminate(t_cmd *cmd)
{
	t_clist		*clistcmd;
	t_subshell	*subcmd;

	if (cmd == 0)
		return (0);
	if (cmd->type == EXEC_T)
		handle_nul_exec(cmd);
	else if (cmd->type == REDIR_T)
		handle_nul_redir(cmd);
	else if (cmd->type == PIPE_T)
		handle_nul_pipe(cmd);
	else if (cmd->type == HERDOC_T)
		handle_nul_herdoc(cmd);
	else if (cmd->type == AND_T || cmd->type == OR_T)
	{
		clistcmd = (t_clist *)cmd;
		nulterminate(clistcmd->left);
		nulterminate(clistcmd->right);
	}
	else if (cmd->type == SUBSHELL_T)
	{
		subcmd = (t_subshell *)cmd;
		nulterminate(subcmd->subcmd);
	}
	return (cmd);
}
