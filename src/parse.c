/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:45:53 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/16 19:35:47 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*execcmd(void)
{
	t_exec	*cmd;

	cmd = malloc(sizeof(*cmd));
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

t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->base.type = REDIR_T;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q;
	char *eq;

	while(find_next_token(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);

		if(get_token(ps, es, &q, &eq) != OTHER)
			exit_error("missing file for redirection");
		if (tok == REDIR_FROM)
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
		else if (tok == REDIR_TO)
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		else if (tok == REDIR_ADD)
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT|O_APPEND, 1);
	}
	return (cmd);
}
t_cmd	*parseexec(char **ps, char *es)
{
	char *q;
	char *eq;
	t_exec	*cmd;
	t_cmd	*ret;
	int	token;
	int i;

	ret = execcmd();
	cmd = (t_exec *)ret;
	i = 0;
	ret = parseredirs(ret, ps, es);
	while(!find_next_token(ps, es, "|&"))
	{
		token = get_token(ps, es, &q, &eq);

		if (token == 0)
			break;
		if (token != OTHER)
			exit_error("syntax error");
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

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (find_next_token(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	// TODO find &&
	return (cmd);
}

t_cmd	*nulterminate(t_cmd *cmd)
{
	int i;
	t_exec *ecmd;
	//t_list *lcmd;
	t_pipe *pcmd;
	t_redir *rcmd;

	if(cmd == 0)
		return 0;

	if(cmd->type == EXEC_T)
	{
		ecmd = (t_exec*)cmd;
		for(i=0; ecmd->argv[i]; i++)
		*ecmd->eargv[i] = 0;
	}
	else if(cmd->type == REDIR_T)
	{
		rcmd = (t_redir*)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if(cmd->type == PIPE_T)
	{
		pcmd = (t_pipe*)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
	// else if(cmd->type == LIST_T)
	// {
	// 	lcmd = (t_list*)cmd;
	// 	nulterminate(lcmd->left);
	// 	nulterminate(lcmd->right);
	// }
	return (cmd);
}

t_cmd	*parsecmd(char *s)
{
	char *es;
	t_cmd *cmd;

	es = s + (ft_strlen(s));
	cmd = parseline(&s, es);
	find_next_token(&s, es, "");
	if(s != es)
	{
		printf("left overs: %s\n", s);
		exit_error("syntax error");
	}
	nulterminate(cmd);
	return (cmd);
}
