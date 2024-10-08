/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:25:34 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:08:33 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// DESCRIPTION
//        The  memcpy()  function  copies n bytes from memory area src to memory
//        area dest. The memory areas must not overlap.  

// RETURN VALUE
//        The memcpy() function returns a pointer to dest.

// #include <stdio.h>
// int main(){
// 	char s[] = "Hello";
// 	char d[] = "Prague";	
// 	size_t n = 3;
// 	ft_memcpy(d, s, n);
// 	memcpy(d,s,n);
// 	printf("ft_memcpy -> d: %s\n",d);
// 	printf("memcpy -> d: %s\n",d);

// }