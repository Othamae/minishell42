/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:41:27 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/24 13:00:42 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	match_pattern_while(char *name, char *pattern, int *s_ind, int *n_ind)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i] && name[j])
	{
		if (pattern[i] == '*')
		{
			*s_ind = i;
			*n_ind = j;
			i++;
		}
		else if (pattern[i] == name[j])
			set_values(&i, i + 1, &j, j + 1);
		else if (*s_ind != -1)
		{
			set_values(&i, *s_ind + 1, &j, *n_ind + 1);
			(*n_ind)++;
		}
		else
			return (0);
	}
	return ((pattern[i] == '\0' && name[j] == '\0')
		|| (pattern[i - 1] == '*' && name[j] != '\0'));
}

int	match_pattern(char *name, char *pattern)
{
	int	star_index;
	int	name_index;

	star_index = -1;
	name_index = -1;
	if (name[0] == '.' && pattern[0] != '.')
		return (0);
	if (pattern[0] == '*' && pattern[1] == '\0')
	{
		if (name[0] == '.')
			return (0);
		else
			return (1);
	}
	return (match_pattern_while(name, pattern, &star_index, &name_index));
}

void	detect_pattern(char **ps, char *es, char *pattern, size_t *pattern_len)
{
	size_t	len;

	len = 0;
	while (*ps < es && !ft_strchr(" \t\n", **ps))
	{
		if (len + 1 >= MAX_BUFFER_SIZE)
			exit_error("Pattern too long");
		pattern[len++] = **ps;
		(*ps)++;
	}
	pattern[len] = '\0';
	*pattern_len = len;
}

int	process_directory(char *path, char *pattern, t_wildbuff *buf)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			entry_len;
	int				expanded;

	dir = opendir(path);
	if (!dir)
		exit_error("opendir failed");
	expanded = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(entry->d_name, pattern))
		{
			entry_len = ft_strlen(entry->d_name);
			ensure_buffer_capacity(buf, entry_len + 2);
			ft_memcpy(buf->buffer + buf->len, entry->d_name, entry_len);
			buf->len += entry_len;
			buf->buffer[buf->len++] = ' ';
			expanded = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (expanded);
}

void	expand_wildcards_buff(char **ps, char **es, t_wildbuff *buf)
{
	size_t		pattern_len;
	char		pattern[MAX_BUFFER_SIZE];
	int			expanded;

	buf->buffer = malloc(MAX_BUFFER_SIZE);
	if (!buf->buffer)
		exit_error("malloc failed");
	buf->len = 0;
	buf->size = MAX_BUFFER_SIZE;
	while (*ps < *es)
	{
		skip_whitespace(ps, *es);
		if (*ps >= *es)
			break ;
		detect_pattern(ps, *es, pattern, &pattern_len);
		expanded = process_directory(".", pattern, buf);
		if (!expanded)
			copy_literal_pattern(pattern, pattern_len, buf);
	}
	finalize_buffer(buf);
	*ps = buf->buffer;
	*es = buf->buffer + buf->len;
}
