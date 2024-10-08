/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:07:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:54 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_xlen(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num >= 1)
	{
		len++;
		num /= 16;
	}
	return (len);
}

static char	*ft_xstr(unsigned long int num, char *str, size_t len)
{
	int	mod;

	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	len--;
	while (len != (size_t)-1)
	{
		mod = num % 16;
		if (mod < 10)
			str[len] = mod + '0';
		else if (mod >= 10)
			str[len] = (mod - 10) + 'a';
		num = num / 16;
		len--;
	}
	return (str);
}

char	*ft_xtoa(unsigned long int num, int is_upper)
{
	size_t	len;
	char	*str;
	int		i;

	len = ft_xlen(num);
	str = 0;
	str = ft_xstr(num, str, len);
	if (!str)
		return (NULL);
	if (is_upper == 1)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'f')
				str[i] -= 32;
			i++;
		}
	}
	return (str);
}
