/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:40:59 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:09:14 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	s2 = malloc (s_len * sizeof(char));
	if (!s2)
		return (0);
	ft_strlcpy(s2, s, s_len);
	return (s2);
}
// DESCRIPTION
//        The strdup() function returns a pointer to a new string which is a du‐
//        plicate of the string s.  Memory for the new string is  obtained  with
//        malloc(3), and can be freed with free(3).

//      
// RETURN VALUE
//        On  success, the strdup() function returns a pointer to the duplicated
//        string.  It returns NULL if insufficient memory  was  available,  with
//        errno set to indicate the cause of the error.

// #include <stdio.h>
// #include "ft_strlen.c"
// #include "ft_strlcpy.c"
// int main(){
// 	char s[] = "Hello";
// 	printf("d: %s\n",ft_strdup(s));
// 	printf("d: %s\n",strdup(s));

// }