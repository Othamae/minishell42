/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:50:33 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/27 22:17:21 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	refresh_list(t_gnl_list **list)
{
	t_gnl_list	*new_node;
	t_gnl_list	*last_node;
	char		*buff;

	if (!list || !*list)
		return ;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return ;
	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
	{
		free(buff);
		return ;
	}
	last_node = get_last_node(*list);
	fill_list(last_node, buff, new_node);
	free_list(list, new_node, buff, 0);
}

int	found_newline(t_gnl_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	create_list(t_gnl_list **list, int fd)
{
	int		char_read;
	char	*buff;

	while (!found_newline(list[fd]))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		char_read = read(fd, buff, BUFFER_SIZE);
		if (char_read == 0)
		{
			free(buff);
			return ;
		}
		if (char_read == -1)
		{
			free(buff);
			free_list(&list[fd], NULL, NULL, 1);
			return ;
		}
		buff[char_read] = '\0';
		append(list, buff, fd);
	}
}

char	*found_line(t_gnl_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = get_line_len(list);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list[4096];
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(list[fd]);
		list[fd] = NULL;
		return (NULL);
	}
	create_list(list, fd);
	if (!list[fd])
		return (NULL);
	next_line = found_line(list[fd]);
	refresh_list(&list[fd]);
	return (next_line);
}

// # include <fcntl.h>

// int	main(){
// 	int fd;
// 	char *line;
// 	int	lines;
// 	lines = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 		printf("%d -> %s\n", lines++, line);
// }