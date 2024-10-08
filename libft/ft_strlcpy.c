/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:29:26 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/24 09:29:47 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
// DESCRIPTION
//      The strlcpy() copy strings.Take the full size of the buffer (not
//      just the length) and guarantee to NUL-terminate the result (as long as
//      size is larger than 0).  Note that a byte for the NUL should be
//      included in size. For strlcpy() src must be NUL-terminated

//      The strlcpy() function copies up to size - 1 characters from the NUL-
//      terminated string src to dst, NUL-terminating the result.

// RETURN VALUES
//      The strlcpy() return the total length of the string they
//		tried to create. That means the length of src.

// #include <stdio.h>
// #include "ft_strlen.c"
// int main(){
// 	char s[] = "Hello";
// 	char d[] = "Brother";
// 	size_t size = 3;
// 	ft_strlcpy(d,s,size);
// 	printf("size of dest: %ld\n",ft_strlcpy(d,s,size));

// }