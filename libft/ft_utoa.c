/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:04:59 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:51 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ulen(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num >= 1)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static char	*ft_ustr(unsigned int num, char *str, size_t len)
{
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	len--;
	while (len)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	str[0] = (num % 10) + '0';
	return (str);
}

char	*ft_utoa(unsigned int num)
{
	size_t	len;
	char	*str;

	len = ft_ulen(num);
	str = 0;
	str = ft_ustr(num, str, len);
	if (!str)
		return (NULL);
	return (str);
}
