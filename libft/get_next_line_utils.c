/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:16:00 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/27 22:17:54 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_list(t_gnl_list *last_node, char *buff, t_gnl_list *new_node)
{
	int		i;
	int		j;

	i = 0;
	while (last_node->str_buff[i] != '\n'
		&& last_node->str_buff[i])
		i++;
	j = 0;
	while (last_node->str_buff[i] && last_node->str_buff[++i])
		buff[j++] = last_node->str_buff[i];
	buff[j] = '\0';
	new_node->str_buff = buff;
	new_node->next = NULL;
}
