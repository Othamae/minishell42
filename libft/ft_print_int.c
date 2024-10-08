/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:17:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:55:58 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_sign(int n, t_data *data)
{
	int	count;

	count = 0;
	if (n < 0 && data->flags.precision == -1 && n != INT_MIN)
	{
		count += ft_print_c('-');
		data->flags.width--;
	}
	else if (data->flags.plus == 1)
		count += ft_print_c('+');
	else if (data->flags.space == 1)
	{
		count += ft_print_c(' ');
		data->flags.width--;
	}
	return (count);
}

static int	ft_print_i(const char *nbstr, int n, t_data *data)
{
	int	counter;

	counter = 0;
	if (n < 0 && n != INT_MIN)
	{
		if (data->flags.zero == 0 || data->flags.precision >= 0)
			counter += ft_print_c('-');
	}
	else if (data->flags.plus == 1 && data->flags.zero == 0 && n != INT_MIN)
		counter += ft_print_c('+');
	else if (data->flags.space == 1 && data->flags.zero == 0 && n != INT_MIN)
		counter += ft_print_c(' ');
	if (data->flags.precision >= 0)
		counter += ft_pad_width(data->flags.precision - 1,
				ft_strlen(nbstr) - 1, 1);
	counter += ft_print_s(nbstr, strlen(nbstr));
	return (counter);
}

int	ft_print_nbstr(char *nbstr, int n, t_data *data)
{
	int	counter;

	counter = 0;
	if (data->flags.zero == 1)
		counter += ft_print_sign(n, data);
	if (data->flags.left == 1)
		counter += ft_print_i(nbstr, n, data);
	if (data->flags.precision >= 0 && (size_t)data->flags.precision
		< ft_strlen(nbstr))
		data->flags.precision = ft_strlen(nbstr);
	if (data->flags.precision >= 0)
	{
		data->flags.width -= data->flags.precision;
		if (n < 0 && data->flags.zero == 1)
			data->flags.width -= 1;
		counter += ft_pad_width(data->flags.width, 0, 0);
	}
	else
		counter += ft_pad_width(data->flags.width - data->flags.plus
				- data->flags.space, ft_strlen(nbstr), data->flags.zero);
	if (data->flags.left == 0)
		counter += ft_print_i(nbstr, n, data);
	return (counter);
}

int	ft_print_int(int n, t_data	*data)
{
	char	*nbstr;
	long	nb;
	int		counter;

	nb = n;
	counter = 0;
	if (nb < 0 && nb != INT_MIN)
	{
		nb *= -1;
		if (data->flags.zero == 0)
			data->flags.width--;
	}
	if (data->flags.precision == 0 && nb == 0)
	{
		counter += ft_pad_width(data->flags.width, 0, 0);
		return (counter);
	}
	nbstr = ft_itoa(nb);
	if (!nbstr)
		return (0);
	counter += ft_print_nbstr(nbstr, n, data);
	free(nbstr);
	return (counter);
}
