/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:35:01 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/24 09:35:10 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && s1[i] == s2[i]
		&& (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// DESCRIPTION
//        The strncmp() function is similar, except it com‐
//        pares only the first (at most) n bytes of s1  and
//        s2. 
//        returns an integer indicating the result
//        of the comparison, as follows:

//        • 0, if the s1 and s2 are equal;
//        • a negative value if s1 is less than s2;
//        • a positive value if s1 is greater than s2.

// RETURN VALUE
//        an integer less than, equal to, or greater than zero
//        if  s1  (or  the first n bytes thereof) is found,
//        respectively, to be less than, to  match,  or  be
//        greater than s2.

// #include <stdio.h>
// int	main()
// {
// 	printf("%d\n", ft_strncmp("Hello world", "lo",2)); // -36
// 	printf("%d\n", strncmp("Hello world", "lo",2)); // -36
// }