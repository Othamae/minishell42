/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:39:30 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:06:50 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	n;
	int	sign;

	while (*s != '\0' && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	sign = 1;
	if (*s != '\0' && (*s == '-' || *s == '+'))
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	n = 0;
	while (*s != '\0' && (*s >= '0' && *s <= '9'))
	{
		n *= 10;
		n += *s - 48;
		s++;
	}
	return (n * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main()
// {
// 	printf("%d\n", ft_atoi("       -13254dsfsvds"));
// 	printf("%d\n", atoi("       -13254dsfsvds"));
// }