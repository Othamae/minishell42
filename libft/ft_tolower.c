/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:32:12 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/24 09:32:19 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	printf("%d\n", ft_tolower('H')); // 104 = 'h'
// 	printf("%d\n", tolower('H'));
// }