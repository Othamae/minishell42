/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:33:05 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:09:09 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = c;
	while (*s != ch)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}
// DESCRIPTION
//        The strchr() function returns a  pointer  to  the
//        first occurrence of the character c in the string
//        s.

// RETURN VALUE
//        a pointer to the matched character or NULL if the
//        character is not  found.   The  terminating  null
//        byte is considered part of the string, so that if
//        c is specified as '\0', these functions return  a
//        pointer to the terminator.

// #include <stdio.h>
// int	main()
// {
// 	printf("%s\n", ft_strchr("Hello world", 'l'));
// 	printf("%s\n", strchr("Hello world", 'l'));
// }