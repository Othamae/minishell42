/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:38:33 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/24 09:38:39 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s2_len = ft_strlen(s2);
	if (s1 == s2 || s2_len == 0)
		return ((char *)s1);
	i = 0;
	while (i < n && (s1[i] != '\0'))
	{
		j = 0;
		while (s1[i + j] != '\0' && s2[j] != '\0'
			&& (i + j) < n && s1[i + j] == s2[j])
		{
			j++;
			if ((j == n && j == s2_len) || j == s2_len)
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (0);
}

// DESCRIPTION
//      The strnstr() function locates the first occurrence
//      of the null-terminated string little in the string
//      big, where not more than len characters are
//      searched.  Characters that appear after a ‘\0’
//      character are not searched. 

// RETURN VALUES
//      If little is an empty string, big is returned; if
//      little occurs nowhere in big, NULL is returned;
//      otherwise a pointer to the first character of the
//      first occurrence of little is returned.	 

// #include <stdio.h>
//  #include "ft_strlen.c"
// int	main()
// {
// 	const char *s1 = "hello"; // BIG
// 	const char *s2 = "el"; // LITTLE
// 	printf("ft_strnstr: %s\n", ft_strnstr(s1, s2, 3));
// }