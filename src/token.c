/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:11:55 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/20 19:26:44 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_whitespace(char **s, char *es)
{
	while (*s < es && ft_strchr(WHITESPACE, **s))
		(*s)++;
}

static int	handle_token(char **s, char c, int ret_value)
{
	int	ret;

	ret = c;
	(*s)++;
	if (**s == c)
	{
		ret = ret_value;
		(*s)++;
	}
	return (ret);
}

static int	handle_special_tokens(char **s, char current_token)
{
	if (current_token == OPEN_P || current_token == CLOSE_P)
	{
		(*s)++;
		return (current_token);
	}
	else if (current_token == PIPE)
		return (handle_token(s, PIPE, OR));
	else if (current_token == REDIR_TO)
		return (handle_token(s, REDIR_TO, REDIR_ADD));
	else if (current_token == REDIR_FROM)
		return (handle_token(s, REDIR_FROM, HERE_DOC));
	else if (current_token == AND && *(*s + 1) == AND)
		return (handle_token(s, AND, AND));
	return (-1);
}

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	skip_whitespace(&s, es);
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	ret = handle_special_tokens(&s, *s);
	if (ret == -1)
	{
		ret = OTHER;
		while (s < es && !ft_strchr(WHITESPACE, *s) && !ft_strchr(SYMBOLS, *s))
			s++;
	}
	if (eq)
		*eq = s;
	skip_whitespace(&s, es);
	*ps = s;
	return (ret);
}

int	find_next_token(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
