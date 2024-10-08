/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:23:25 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:08:45 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return (s);
}

// DESCRIPTION
//        The  memset()  function  fills  the  first  n bytes of the memory area
//        pointed to by s with the constant byte c.

// RETURN VALUE
//        The memset() function returns a pointer to the memory area s.

// #include <stdio.h>
// int main(){
// 	char s1[] = "Hello";
// 	char s2[] = "Hello";
// 	int c = 'a';
// 	size_t n = 2;
// 	ft_memset(s1, c, n);
// 	memset(s2, c, n);
// 	printf("s1: %s\n",s1);
// 	printf("s2: %s\n",s2);

// }