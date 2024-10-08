/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:24:29 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:06:45 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// DESCRIPTION
//        The  bzero()  function  erases  the  data in the n bytes of the memory
//        starting at the location pointed to by s, by writing zeros (bytes con‐
//        taining '\0') to that area.

// RETURN VALUE
//        None.

// #include <stdio.h>
// #include "ft_memset.c"
// int main(){
// 	char s[] = "Hello";
// 	char *s1 = s + 3;
// 	char *s2 = s + 3;
// 	size_t n = 2;
// 	ft_bzero(s1,n);
// 	bzero(s2,n);
// 	printf("s1: %s\n",s);
// 	printf("s2: %s\n",s);

// }