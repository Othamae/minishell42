/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksym.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:41:22 by mac               #+#    #+#             */
/*   Updated: 2024/10/16 19:41:42 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_symbols(char *input)
{
	int i = 0;

	while (input[i] != '\0')
	{
		int j = 0;

		while (SYMBOLS[j] != '\0')
		{
			if (input[i] == SYMBOLS[j])
			{
				return 1;
			}
			j++;
		}
		i++;
	}
	return 0; // No symbols found
}
