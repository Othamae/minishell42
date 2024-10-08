/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:50:12 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:11 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr_base(int n, char *base, t_data *data)
{
	int				counter;
	int				base_len;
	long long int	nb;

	counter = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		counter += ft_print_char('-', data);
	}
	base_len = ft_strlen(base);
	if (nb >= (long long int)base_len)
	{
		counter += ft_print_nbr_base(nb / base_len, base, data);
		counter += ft_print_nbr_base(nb % base_len, base, data);
	}
	else
		counter += ft_print_c(base[nb % base_len]);
	return (counter);
}
