/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:50:10 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:07:35 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long nbr)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		counter++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		counter++;
		nbr /= 10;
	}
	return (counter);
}

static char	*n_zero(char *str)
{
	str[0] = '0';
	return (str);
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*str;
	long	n;

	n = nbr;
	len = nbr_len(n);
	str = (char *) malloc((len +1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		return (n_zero(str));
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (str);
}

// Return value: The string representing the integer.
// NULL if the allocation fails. 
// Description: returns a string representing
// integer received as an argument.
// Negative numbers must be handled.

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n", ft_itoa(1342345));
// 	printf("%s\n", ft_itoa(-1342345));
// }
