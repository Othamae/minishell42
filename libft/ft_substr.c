/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:58:38 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:10:15 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start
		|| ft_strlen(s) <= (size_t)start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	dest = malloc((len +1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// Return value: The substring. NULL if the allocation fails. 
// Description Allocates and returns a substring from the string ’s’. 
// The substring begins at index ’start’ and is of maximum size ’len’.

// #include <stdio.h>
// #include "ft_strlcpy.c"
// #include "ft_strlen.c"
// #include "ft_strdup.c"
// int main () 
// {
// 	char s[] = "Hello my friend";
// 	int start = 9;
// 	size_t len = 3;
// 	printf("%s\n",ft_substr(s, start, len) );

// }