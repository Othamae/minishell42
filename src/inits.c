/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:44:08 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/01 13:01:22 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*execcmd(void)
{
	t_exec	*cmd;

	cmd = safe_malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->base.type = EXEC_T;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->base.type = PIPE_T;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, t_redir_info info)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->base.type = REDIR_T;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->info = info;
	return ((t_cmd *)cmd);
}

t_cmd	*heredoccmd(char *delim, t_cmd *subcmd)
{
	t_herdoc	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->base.type = HERDOC_T;
	cmd->delim = ft_strdup(delim);
	cmd->right = subcmd;
	return ((t_cmd *)cmd);
}

t_cmd	*listcmd(t_cmd *left, t_cmd *right, int type)
{
	t_clist	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->base.type = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
