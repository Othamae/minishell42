/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:37:29 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:08:29 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
// DESCRIPTION
//        The  memcmp() function compares the first n bytes
//        (each interpreted as unsigned char) of the memory
//        areas s1 and s2.

// RETURN VALUE
//        The  memcmp()  function  returns  an integer less
//        than, equal to, or greater than zero if the first
//        n  bytes of s1 is found, respectively, to be less
//        than, to match, or be greater than  the  first  n
//        bytes of s2.

//        For  a  nonzero  return value, the sign is deter‐
//        mined by the sign of the difference  between  the
//        first  pair  of  bytes  (interpreted  as unsigned
//        char) that differ in s1 and s2.

//        If n is zero, the return value is zero.

// #include <stdio.h>
//  #include <string.h>
// int main(){
// 	char s1[] = "Hello";
// 	char s2[] = "Hd";
// 	size_t n = 2;

// 	printf("ft_memcmp -> s1: %d\n",ft_memcmp(s1, s2, n));
// 	printf("memcmp -> s1: %d\n",memcmp(s1, s2, n));

// }