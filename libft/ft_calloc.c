/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:40:17 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:06:55 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	m;

	if ((nmemb == 0 || size == 0))
	{
		ptr = malloc(0);
		return (ptr);
	}
	m = nmemb * size;
	if (m / nmemb != size)
		return (NULL);
	ptr = malloc(m);
	if (!ptr)
		return (0);
	ft_bzero(ptr, m);
	return (ptr);
}
// DESCRIPTION
//        The calloc() function allocates memory for an ar‐
//        ray of nmemb elements of size bytes each and  re‐
//        turns  a  pointer  to  the allocated memory.  The
//        memory is set to zero.  If nmemb or  size  is  0,
//        then  calloc()  returns  either NULL, or a unique
//        pointer value  that  can  later  be  successfully
//        passed to free(). 

// RETURN VALUE
//        a pointer to the allocated memory, which  is  suit‐
//        ably  aligned  for  any built-in type.  On error,
//        these functions return NULL.  NULL  may  also  be
//        returned  by a successful call to calloc()
//        with nmemb or size equal to zero.

// #include <stdio.h>
// #include "ft_bzero.c"
// #include "ft_memset.c"
// int main ()
// {
//  	size_t nmemb = 5; 
//     size_t size = sizeof(int); 
//     int *ptr = (int *)ft_calloc(nmemb, size);

// 	if (!ptr) 	
// 		printf("Error");
// 	printf("memory allocated\n");
// 	 for (size_t i = 0; i < nmemb; i++) {
//         printf("%d ", ptr[i]);
//     }
//     printf("\n");
// }