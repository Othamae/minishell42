/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:00 by mac               #+#    #+#             */
/*   Updated: 2024/11/09 12:20:18 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*safe_malloc(size_t bytes)
{
	void	*new_str;

	new_str = (char *)malloc(bytes);
	if (new_str == NULL)
	{
		printf("error allocating new string");
		return (0);
	}
	return (new_str);
}

void	print_str(char *old_str, char *new_str, int no_newline)
{
	if (no_newline)
		printf("%s", new_str);
	else
		printf("%s\n", new_str);
	if (new_str != old_str)
		free(new_str);
}

int	handle_null(int no_newline)
{
	if (no_newline)
		;
	else
		printf("\n");
	return (0);
}
