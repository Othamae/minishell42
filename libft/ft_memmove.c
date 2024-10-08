/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:28:24 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:08:36 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src && n)
		return (NULL);
	if (dest > src)
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

// DESCRIPTION
//        The  memmove()  function copies n bytes from memory area src to memory
//        area dest.  The memory areas  may  overlap:  copying  takes  place  as
//        though  the  bytes in src are first copied into a temporary array that
//        does not overlap src or dest, and the bytes are then copied  from  the
//        temporary array to dest.

// RETURN VALUE
//        The memmove() function returns a pointer to dest.

// #include <stdio.h>
// int main(){
// 	// char s[] = "Hello";
// 	// char d[10] = "Bro";
// 	// char d2[10] = "Bro";

// 	char *s = NULL;
// 	char *d = NULL;
// 	char *d2 = NULL;

// 	size_t n = 5;
// 	ft_memmove(d, s, n);
// 	printf("ft_memmove -> d: %s\n",d);
// 	memmove(d2,s,n);
// 	printf("memmove -> d: %s\n",d2);

// }