/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:11:55 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/12 11:54:13 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;

	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	
	if (q)
		*q = s;
	ret = *s;

	if (*s == 0)
		return (0);
	if(*s == PIPE || *s == ENV_VA)
		s++;
	else if(*s == REDIR_TO)
	{
		s++;
		if (*s == REDIR_TO)
		{
			ret = REDIR_ADD;
			s++;
		}
	}
	else if (*s == REDIR_FROM)
	{
		s++;
		if (*s == REDIR_FROM)
		{
			ret = HERE_DOC;
			s++;
		}
	}
	else 
	{
		ret = OTHER;
		while (s < es && !ft_strchr(WHITESPACE, *s) && !ft_strchr(SYMBOLS, *s))
			s++;
	}

	if (eq)
		*eq = s;
	
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	
	*ps = s;
	return (ret);
}

int	find_next_token(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	while(s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
