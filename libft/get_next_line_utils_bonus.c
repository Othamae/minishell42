/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:50:47 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/27 22:17:44 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl_list	*get_last_node(t_gnl_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	append(t_gnl_list **list, char *buff, int fd)
{
	t_gnl_list	*new_node;
	t_gnl_list	*last_node;

	last_node = get_last_node(list[fd]);
	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buff;
	new_node->next = NULL;
}

int	get_line_len(t_gnl_list *list)
{
	int	len;
	int	i;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_gnl_list *list, char *str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	i = 0;
	while (list)
	{
		j = 0;
		while (list->str_buff[j])
		{
			if (list->str_buff[j] == '\n')
			{
				str[i++] = '\n';
				str[i] = '\0';
				return ;
			}
			str[i++] = list->str_buff[j++];
		}
		list = list->next;
	}
	str[i] = '\0';
}

void	free_list(t_gnl_list **list, t_gnl_list *new_node, char *buff,
			int free_only)
{
	t_gnl_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str_buff);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (!free_only)
	{
		if (new_node)
		{
			if (new_node->str_buff && new_node->str_buff[0])
				*list = new_node;
			else
			{
				free(buff);
				free(new_node);
			}
		}
		else
			free(buff);
	}
}
