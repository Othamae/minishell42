/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:03:31 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/28 11:42:14 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			counter++;
		if (i > 0 && s[i] != c && s[i - 1] == c)
			counter++;
		i++;
	}
	return (counter);
}

static int	str_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*save_string(char const *s, char c)
{
	char	*str;
	int		i;
	int		s_len;

	s_len = str_len(s, c);
	str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		s_count;
	int		i;

	if (!s)
		return (NULL);
	s_count = str_count(s, c);
	array = malloc((s_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			array[i] = save_string(s, c);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	array[i] = NULL;
	return (array);
}

// Return value: The array of new strings resulting from the split.
// NULL if the allocation fails. 
// Description returns an array of strings obtained by splitting ’s’ 
// using the character ’c’ as a delimiter. The array must end
// with a NULL pointer.

// #include <stdio.h>
// int	main()
// {
// 	int		index;
// 	char	**split;
// 	split = ft_split(" Hello world from 42 Prague", ' ');
// 	index = 0;
// 	while (split[index])
// 	{
// 		printf("%s\n", split[index]);
// 		index++;
// 	}
// }