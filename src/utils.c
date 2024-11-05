/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:05:10 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/05 20:04:57 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_error(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	return (pid);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int	count_char(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*mkcopy(char *q, char *eq)
{
	int		len;
	char	*copy;

	len = eq - q;
	copy = malloc(len + 1);
	if (!copy)
		exit_error("memory allocation error");
	ft_strlcpy(copy, q, len + 1);
	copy[len] = '\0';
	return (copy);
}
