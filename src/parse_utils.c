/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:11:51 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/23 15:06:00 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_cmd	*handle_redir_from(t_cmd *cmd, char *q, char *eq)
{
	t_redir_info	info;

	info.mode = O_RDONLY;
	info.fd = 0;
	return (redircmd(cmd, q, eq, info));
}

static t_cmd	*handle_redir_to(t_cmd *cmd, char *q, char *eq)
{
	t_redir_info	info;

	info.mode = O_WRONLY | O_CREAT | O_TRUNC;
	info.fd = 1;
	return (redircmd(cmd, q, eq, info));
}

static t_cmd	*handle_redir_add(t_cmd *cmd, char *q, char *eq)
{
	t_redir_info	info;

	info.mode = O_WRONLY | O_CREAT | O_APPEND;
	info.fd = 1;
	return (redircmd(cmd, q, eq, info));
}

t_cmd	*handle_parseredirs(t_cmd *cmd, char *q, char *eq, int tok)
{
	if (tok == REDIR_FROM)
		cmd = handle_redir_from(cmd, q, eq);
	else if (tok == REDIR_TO)
		cmd = handle_redir_to(cmd, q, eq);
	else if (tok == REDIR_ADD)
		cmd = handle_redir_add(cmd, q, eq);
	else if (tok == HERE_DOC)
		cmd = heredoccmd(q, cmd);
	return (cmd);
}

t_cmd	*handle_parseexec(char **ps, char *es, t_exec *cmd, t_cmd *ret)
{
	int		token;
	char	*q;
	char	*eq;
	int		i;

	i = 0;
	while (!find_next_token(ps, es, "|&)"))
	{
		token = get_token(ps, es, &q, &eq);
		if (token == 0)
			break ;
		if (token != OTHER)
			exit_error("syntax error\n");
		cmd->argv[i] = q;
		cmd->eargv[i] = eq;
		i++;
		if (i >= MAXARGS)
			exit_error("Too many arguments");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[i] = 0;
	cmd->eargv[i] = 0;
	return (ret);
}
