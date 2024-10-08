/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:47:59 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:55:54 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_char(int c, t_data	*data)
{
	int	counter;

	counter = 0;
	if (data->flags.left == 1)
		counter += ft_print_c(c);
	counter += ft_pad_width(data->flags.width, 1, data->flags.zero);
	if (data->flags.left == 0)
		counter += ft_print_c(c);
	return (counter);
}
