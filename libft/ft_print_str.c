/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:51:23 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:19 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(const char *str, int precision)
{
	int	counter;

	counter = 0;
	while (str[counter] && counter < precision)
		counter += ft_print_c(str[counter]);
	return (counter);
}

static int	ft_print_string(const char *str, t_data *data)
{
	int	counter;

	counter = 0;
	if (data->flags.precision >= 0)
	{
		counter += ft_pad_width(data->flags.precision, ft_strlen(str), 0);
		counter += ft_print_s(str, data->flags.precision);
	}
	else
		counter += ft_print_s(str, ft_strlen(str));
	return (counter);
}

int	ft_print_str(const char *str, t_data *data)
{
	int	counter;

	counter = 0;
	if (str == NULL && data->flags.precision >= 0 && data->flags.precision < 6)
	{
		counter += ft_pad_width(data->flags.width, 0, 0);
		return (counter);
	}
	if (str == NULL)
		str = "(null)";
	if (data->flags.precision >= 0 && (size_t)data->flags.precision
		> ft_strlen(str))
		data->flags.precision = ft_strlen(str);
	if (data->flags.left == 1)
		counter += ft_print_string(str, data);
	if (data->flags.precision >= 0)
		counter += ft_pad_width(data->flags.width, data->flags.precision, 0);
	else
		counter += ft_pad_width(data->flags.width, ft_strlen(str), 0);
	if (data->flags.left == 0)
		counter += ft_print_string(str, data);
	return (counter);
}
