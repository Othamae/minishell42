/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:27:10 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/10 15:20:22 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_token_end(char *str, const char *delim, int start)
{
	int	i;
	int	in_quote;

	i = start;
	in_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (in_quote == 0)
				in_quote = str[i];
			else if (in_quote == str[i])
				in_quote = 0;
		}
		else if (ft_strchr(delim, str[i]) != NULL && in_quote == 0)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*svd_s = NULL;
	char		*token;
	int			start;
	int			token_end;

	start = 0;
	if (str != NULL)
		svd_s = str;
	if (svd_s == NULL)
		return (NULL);
	while (svd_s[start] != '\0' && ft_strchr(delim, svd_s[start]) != NULL)
		start++;
	token_end = find_token_end(svd_s, delim, start);
	token = &svd_s[start];
	if (svd_s[token_end] != '\0')
	{
		svd_s[token_end] = '\0';
		svd_s = &svd_s[token_end + 1];
	}
	else
		svd_s = NULL;
	return (token);
}

int	only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
			&& *str != '\v' && *str != '\f' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}
