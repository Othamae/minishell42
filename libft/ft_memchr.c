/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:36:26 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:08:24 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
// DESCRIPTION
//        The  memchr()  function scans the initial n bytes
//        of the memory area pointed to by s for the  first
//        instance  of c.  Both c and the bytes of the mem‐
//        ory area pointed to by s are interpreted  as  un‐
//        signed char.

// RETURN VALUE
//        a pointer to the matching byte or NULL if the char‐
//        acter does not occur in the given memory area.

// #include <stdio.h>
//  #include <string.h>
// int main(){
// 	char s1[] = "Hello";
// 	int c = 'e';
// 	size_t n = 2;

// 	printf("ft_memchr -> s1: %p\n",ft_memchr(s1, c, n));
// 	printf("memchr -> s1: %p\n",memchr(s1, c, n));

// }