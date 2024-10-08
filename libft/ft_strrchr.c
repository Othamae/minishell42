/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:34:15 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:10:06 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*p;
	unsigned char	ch;

	p = (char *)s + ft_strlen(s);
	ch = c;
	if (ch == '\0')
		return (p++);
	while (p >= s)
	{
		if (*p == ch)
			return (p);
		p--;
	}
	return (0);
}
// DESCRIPTION
//        The strrchr() function returns a pointer  to  the
//        last  occurrence of the character c in the string
//        s.

// RETURN VALUE
//        a pointer  to  the matched character or NULL if the
//        character is not  found.   The  terminating  null
//        byte is considered part of the string, so that if
//        c is specified as '\0', these functions return  a
//        pointer to the terminator.

// #include <stdio.h>
// #include "ft_strlen.c"
// int	main()
// {
// 	printf("%s\n", ft_strrchr("Hello world", 'a'));
// 	printf("%s\n", strrchr("Hello world", 'a'));
// }