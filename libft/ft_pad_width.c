/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:01:25 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/21 10:55:38 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pad_width(int total_width, int size, int zero)
{
	int	count;

	count = 0;
	while (total_width - size > 0)
	{
		if (zero)
			count += ft_print_c('0');
		else
			count += ft_print_c(' ');
		total_width--;
	}
	return (count);
}
