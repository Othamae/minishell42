/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:38:42 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:23 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hash(int upper)
{
	int	counter;

	counter = 0;
	counter += ft_print_c('0');
	if (upper == 1)
		counter += ft_print_c('X');
	else
		counter += ft_print_c('x');
	return (counter);
}

static char	*ft_get_nbrstr(unsigned int n, int base_len, int upper)
{
	char	*nbrstr;

	nbrstr = "";
	if (base_len == 10)
		nbrstr = ft_utoa(n);
	else if (base_len == 16)
		nbrstr = ft_xtoa(n, upper);
	return (nbrstr);
}

static int	ft_print_precision(char *nbrstr, t_flags *flags)
{
	int	counter;

	counter = 0;
	if (flags->precision >= 0 && (size_t)flags->precision
		< ft_strlen(nbrstr))
		flags->precision = ft_strlen(nbrstr);
	if (flags->precision >= 0)
	{
		if (flags->left == 0)
		{
			if (flags->width > 0)
				counter += ft_pad_width(flags->width - flags->precision, 0, 0);
			if (ft_strlen(nbrstr) < (size_t)flags->precision)
				counter += ft_pad_width(flags->precision
						- ft_strlen(nbrstr), 0, 1);
		}
		else if (flags->left == 1)
			counter += ft_pad_width(flags->width - flags->plus
					- flags->space - flags->precision, 0, flags->zero);
	}
	else
		counter += ft_pad_width(flags->width - flags->plus
				- flags->space, ft_strlen(nbrstr), flags->zero);
	return (counter);
}

int	ft_print_u(unsigned long long int number, char *base, t_data *data)
{
	int	counter;
	int	base_len;

	counter = 0;
	base_len = ft_strlen(base);
	if (number >= (unsigned long long int)base_len)
	{
		counter += ft_print_nbr_base(number / base_len, base, data);
		counter += ft_print_nbr_base(number % base_len, base, data);
	}
	else
		counter += ft_print_c(base[number % base_len]);
	return (counter);
}

int	ft_print_u_base(unsigned int n, char *base, t_data *data)
{
	int						counter;
	unsigned long long int	number;
	char					*nbrstr;

	counter = 0;
	number = n;
	if (data->flags.hash == 1 && n > 0)
		counter += ft_print_hash(data->upper);
	if (data->flags.precision == 0 && n == 0)
		return (counter += ft_pad_width(data->flags.width, 0, 0));
	nbrstr = ft_get_nbrstr(n, ft_strlen(base), data->upper);
	if (!nbrstr)
		return (0);
	if (data->flags.left == 1)
	{
		if (data->flags.precision >= 0)
			counter += ft_pad_width(data->flags.precision
					- ft_strlen(nbrstr), 0, 1);
		counter += ft_print_u(number, base, data);
	}
	counter += ft_print_precision(nbrstr, &data->flags);
	if (data->flags.left == 0)
		counter += ft_print_u(number, base, data);
	free(nbrstr);
	return (counter);
}
