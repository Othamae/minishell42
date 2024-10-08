/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:00:28 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:10:11 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	first;
	int	last;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	first = 0;
	last = ft_strlen(s1);
	while (in_set(set, s1[first]))
		first++;
	if (first == last)
		return (ft_strdup(""));
	while (last > first && in_set(set, s1[last - 1]))
		last--;
	return (ft_substr(s1, first, last - first));
}
// Return value: The trimmed string. NULL if the allocation fails. 
// Description returns a copy of ’s1’ with the characters specified in ’set’ 
// removed from the beginning and the end of the string.

// #include <stdio.h>
// #include "ft_strlen.c"
// #include "ft_strdup.c"
// #include "ft_substr.c"
// #include "ft_strlcpy.c"
// int main () 
// {
// 	char s1[] = "Hello my friend Hello";
// 	char set[] = "Hello";

// 	printf("%s\n",ft_strtrim(s1, set));

// }