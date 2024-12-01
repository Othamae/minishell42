/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:45:53 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/01 13:41:44 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (find_next_token(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &q, &eq) != OTHER)
		{
			printf("missing file for redirection\n");
			return (NULL);
		}
		cmd = handle_parseredirs(cmd, q, eq, tok);
	}
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_exec	*cmd;
	t_cmd	*ret;

	ret = execcmd();
	cmd = (t_exec *)ret;
	ret = parseredirs(ret, ps, es);
	ret = handle_parseexec(ps, es, cmd, ret);
	return (ret);
}

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parseexec(ps, es);
	if (find_next_token(ps, es, "|"))
	{
		token = get_token(ps, es, 0, 0);
		if (token == OR)
			cmd = listcmd(cmd, parseline(ps, es), OR_T);
		else
			cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	if (find_next_token(ps, es, "("))
	{
		get_token(ps, es, 0, 0);
		cmd = subshellcmd(parseline(ps, es));
		if (find_next_token(ps, es, ")"))
			get_token(ps, es, 0, 0);
		else
			exit_error("syntax error: missing )");
	}
	else
		cmd = parsepipe(ps, es);
	while (find_next_token(ps, es, "&&||"))
	{
		token = get_token(ps, es, 0, 0);
		if (token == AND)
			cmd = listcmd(cmd, parseline(ps, es), AND_T);
		else if (token == OR)
			cmd = listcmd(cmd, parseline(ps, es), OR_T);
	}
	return (cmd);
}

t_cmd	*parsecmd(char *s, t_wildbuff *buf)
{
	char		*es;
	t_cmd		*cmd;

	es = s + (ft_strlen(s));
	handle_d_quotes(s, &es);
	if (ft_strchr(s, '*'))
		expand_wildcards_buff(&s, &es, buf);
	cmd = parseline(&s, es);
	if (!cmd)
		return (NULL);
	find_next_token(&s, es, "");
	if (s != es)
	{
		printf("left overs: %s\n", s);
		printf("syntax error\n");
		return (0);
	}
	nulterminate(cmd);
	return (cmd);
}
