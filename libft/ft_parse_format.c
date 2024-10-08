/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:50:25 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:55:45 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_number_len(const char *s)
{
	int	len;

	len = 0;
	while (*s != '\0' && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (*s != '\0' && (*s >= '0' && *s <= '9'))
	{
		s++;
		len++;
	}
	return (len);
}

static void	ft_get_value(t_data *data, int *value)
{
	*value = ft_atoi(data->s);
	data->s += ft_get_number_len(data->s);
}

static void	ft_parse_flags(t_data *data)
{
	char	flag;

	flag = 0;
	while (ft_strchr("+ 0-#", *data->s))
	{
		flag = *data->s;
		if (flag == '0')
			data->flags.zero = 1;
		else if (flag == '+')
			data->flags.plus = 1;
		else if (flag == ' ')
			data->flags.space = 1;
		else if (flag == '-')
			data->flags.left = 1;
		else if (flag == '#')
			data->flags.hash = 1;
		++data->s;
	}
}

int	ft_parse_format(t_data *data)
{
	ft_memset(&data->flags, 0, sizeof(t_flags));
	data->flags.precision = -1;
	ft_parse_flags(data);
	ft_get_value(data, &data->flags.width);
	if (*data->s == '.' && *(++data->s))
		ft_get_value(data, &data->flags.precision);
	if (!ft_isflag(*data->s))
		return (0);
	data->flags.specifier = *data->s;
	if (data->flags.specifier == 'X')
		data->upper = 1;
	return (1);
}
