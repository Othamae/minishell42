/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:26:36 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/05 20:40:11 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_d_quotes(char *s, char **es)
{
	char	*line;
	size_t	len_s;

	len_s = ft_strlen(s);
	while (has_unclosed_quotes(s))
	{
		line = readline("> ");
		if (!line)
			break ;
		if (len_s + ft_strlen(line) + 2 >= MAX_BUFFER_SIZE)
		{
			free(line);
			exit_error("Error: buffer overflow\n");
		}
		s[len_s] = '\n';
		ft_strlcpy(s + len_s + 1, line, MAX_BUFFER_SIZE - len_s - 1);
		len_s += ft_strlen(line) + 1;
		free(line);
		*es = s + len_s;
	}
}
