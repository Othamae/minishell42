/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:07:14 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 19:36:12 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || (!s && !f))
		return (ft_strdup(""));
	if (!f)
		return (ft_strdup(s));
	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

// Return value: The string created from the successive applications
// of ’f’. NULL if the allocation fails. 
// Description Applies the function f to each character of the
// string s, passing its index as the first argument
// and the character itself as the second. A new
// string is created (using malloc(3)) to collect the
// results from the successive applications of f.

// #include <stdio.h>
// #include "ft_strdup.c"
// #include "ft_strlen.c"
// #include "ft_strlcpy.c"

// char f(unsigned int i, char c)
// {
// 	char str;
// 	if (i != 0)
// 		str = c + 1;
// 	else 
// 		str = c + 1 + i;
// 	return (str);
// }

// int main()
// {
// 	char str1[] = "Hello my friend";
// 	char* str2;
// 	str2 = ft_strmapi(str1, *f);
// 	printf("%s\n", str2);
// }