/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:12:41 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:56:36 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_init_data(t_data *data, const char *format)
{
	char	*str;

	str = ft_strdup(format);
	if (!str || *str == '\0')
		return (0);
	data->chars_written = 0;
	data->s = str;
	data->upper = 0;
	return (1);
}

int	ft_render_format(t_data *data)
{
	int		counter;

	counter = 0;
	if (data->flags.specifier == '%')
		counter += ft_print_c('%');
	else if (data->flags.specifier == 'c')
		counter += ft_print_char(va_arg(data->args, int), data);
	else if (data->flags.specifier == 's')
		counter += ft_print_str(va_arg(data->args, char *), data);
	else if (data->flags.specifier == 'd' || data->flags.specifier == 'i')
		counter += ft_print_int(va_arg(data->args, int), data);
	else if (data->flags.specifier == 'x')
		counter += ft_print_u_base(va_arg(data->args, unsigned int),
				BASE16LOWER, data);
	else if (data->flags.specifier == 'X')
		counter += ft_print_u_base(va_arg(data->args, unsigned int),
				BASE16UPPER, data);
	else if (data->flags.specifier == 'u')
		counter += ft_print_u_base(va_arg(data->args, unsigned int),
				BASE10, data);
	else if (data->flags.specifier == 'p')
		counter += ft_print_ptr(va_arg(data->args, unsigned long long int),
				BASE16LOWER, data);
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	t_data	data;
	char	*s;

	if (!format || *format == '\0')
		return (0);
	va_start(data.args, format);
	if (!ft_init_data(&data, format))
		return (0);
	s = (char *)data.s;
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (!ft_parse_format(&data))
				return (0);
			data.chars_written += ft_render_format(&data);
		}
		else
			data.chars_written += write(1, data.s, 1);
		++data.s;
	}
	va_end(data.args);
	free(s);
	return (data.chars_written);
}
