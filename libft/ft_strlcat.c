/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:30:38 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 20:46:59 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + src_len);
	i = 0;
	while (src[i] != '\0' && (i + dest_len < size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
// DESCRIPTION
//      The strlcat() concatenate strings and guarantee to 
//		NUL-terminate the result (as long as
//      size is larger than 0 or, as long as there is at least 
//		one byte free in dst). 
//		Note that a byte for the NUL should be included in size.  
//      For strlcat() both src and dst must be NUL-terminated.

//      The strlcat() function appends the NUL-terminated string src to the end
//      of dst. It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
//      nating the result.

// RETURN VALUES
//      The strlcat() functions return the total length of the
//      string they tried to create. That means the initial length 
//		of dst plus the length
//      of src.  While this may seem somewhat confusing, it was done to make
//      truncation detection simple. If traverses size characters without find‐
//      ing a NUL, the length of the string is considered to be size and the
//      destination string will not be NUL-terminated (since there was no space
//      for the NUL). 

// #include <stdio.h>
// #include "ft_strlen.c"
// #include <unistd.h>
// #include <bsd/string.h>

// void	ft_print_result(int n)
// {
// 	char c;

// 	if (n >= 10)
// 		ft_print_result(n / 10);
// 	c = n % 10 + '0';
// 	write (1, &c, 1);
// }

// int main(){
// 	// char s[] = "Hello";
// 	// char d[] = "Brother";
// 	// size_t size = 3;
// 	// ft_strlcat(d,s,size);
// 	// printf("size of dest: %ld\n",ft_strlcat(d,s,size));
// 	char *dest;

// 	if (!(dest = (char *)malloc(sizeof(*dest) * 15)))
// 		return (0);

// 	memset(dest, 'r', 15);
// 		ft_print_result(ft_strlcat(dest, "lorem ipsum dolor sit amet", 5));
// 		write(1, "\n", 1);
// 		write(1, dest, 15);
// 		write(1, "\n", 1);

// 		// write(1, "-----------\n", 13);
// 		// ft_print_result(strlcat(dest, "lorem ipsum dolor sit amet", 5));
// 		// write(1, "\n", 1);
// 		// write(1, dest, 15);
// 		// write(1, "\n", 1);
// }