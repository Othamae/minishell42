/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:09:24 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:15 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_p(unsigned long long int n, char *base, t_data *data)
{
	int	counter;
	int	base_len;

	counter = 0;
	base_len = ft_strlen(base);
	if (n >= (unsigned long long int)base_len)
	{
		counter += ft_print_p(n / base_len, base, data);
		counter += ft_print_p(n % base_len, base, data);
	}
	else
		counter += ft_print_c(base[n % base_len]);
	return (counter);
}

static int	ft_ptrlen(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static int	ft_print_nil(int left, int width, int ptrlen)
{
	int	counter;

	counter = ft_print_s("(nil)", 5);
	if (left)
		counter += ft_pad_width(width, ptrlen, 0);
	return (counter);
}

int	ft_print_ptr(unsigned long long int n, char *base, t_data *data)
{
	int	counter;

	counter = 0;
	if (!n)
		data->flags.width -= ft_strlen("(nil)") - 1;
	else
		data->flags.width -= 2;
	if (data->flags.left == 1)
	{
		if (n == 0)
			return (ft_print_nil(1, data->flags.width, ft_ptrlen(n)));
		counter += ft_print_s("0x", 2);
		counter += ft_print_p(n, base, data);
	}
	counter += ft_pad_width(data->flags.width, ft_ptrlen(n), 0);
	if (data->flags.left == 0)
	{
		if (n == 0)
			return (counter += ft_print_nil(0, data->flags.width,
					ft_ptrlen(n)));
		counter += ft_print_s("0x", 2);
		counter += ft_print_p(n, base, data);
	}
	return (counter);
}
