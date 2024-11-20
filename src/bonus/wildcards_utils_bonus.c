/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:47:45 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/20 10:11:00 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_values(int *i, int i_value, int *j, int j_value)
{
	if (i != NULL)
		*i = i_value;
	if (j != NULL)
		*j = j_value;
}

void	ensure_buffer_capacity(t_wildbuff *buf, size_t additional)
{
	char	*new_buffer;

	while (buf->len + additional >= buf->size)
	{
		buf->size *= 2;
		new_buffer = malloc(buf->size);
		if (!new_buffer)
			exit_error("malloc failed");
		ft_memcpy(new_buffer, buf->buffer, buf->len);
		free(buf->buffer);
		buf->buffer = new_buffer;
	}
}

void	copy_literal_pattern(char *pattern, size_t patt_len, t_wildbuff *buf)
{
	ensure_buffer_capacity(buf, patt_len + 2);
	ft_memcpy(buf->buffer + buf->len, pattern, patt_len);
	buf->len += patt_len;
	buf->buffer[buf->len++] = ' ';
}

void	finalize_buffer(t_wildbuff *buf)
{
	if (buf->len > 0 && buf->buffer[buf->len - 1] == ' ')
		buf->len--;
	buf->buffer[buf->len] = '\0';
}
