/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:59:31 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/24 09:59:43 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		dest_len;
	int		i;
	int		j;

	dest_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(dest_len * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
// Return value The new string. NULL if the allocation fails. 
// Description Allocates and returns a new string, 
// which is the result of the concatenation of ’s1’ and ’s2’.

// #include <stdio.h>
// #include "ft_strlen.c"
// int main () 
// {
// 	char s1[] = "Hello ";
// 	char s2[] = "my friend";

// 	printf("%s\n",ft_strjoin(s1, s2));

// }