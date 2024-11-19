/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:41:27 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/18 20:14:07 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			entry_len = strlen(entry->d_name);
			ensure_buffer_capacity(buf, entry_len + 2);
			memcpy(buf->buffer + buf->len, entry->d_name, entry_len);
			buf->len += entry_len;
			buf->buffer[buf->len++] = ' ';
			expanded = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (expanded);
}

void	expand_wildcards_buff(char **ps, char **es)
{
	t_wildbuff	buf;
	size_t		pattern_len;
	char		pattern[MAX_BUFFER_SIZE];
	int			expanded;

	buf.buffer = malloc(MAX_BUFFER_SIZE);
	if (!buf.buffer)
		exit_error("malloc failed");
	buf.len = 0;
	buf.size = MAX_BUFFER_SIZE;
	while (*ps < *es)
	{
		skip_whitespace(ps, *es);
		if (*ps >= *es)
			break ;
		detect_pattern(ps, *es, pattern, &pattern_len);
		expanded = process_directory(".", pattern, &buf);
		if (!expanded)
			copy_literal_pattern(pattern, pattern_len, &buf);
	}
	finalize_buffer(&buf);
	*ps = buf.buffer;
	*es = buf.buffer + buf.len;
}

///////////////////////////////////////////////////////////////////////////////

// void    ensure_buffer_capacity(char **buffer, size_t *len, size_t additional, size_t *size)
// {
//     char    *new_buffer;

//     while (*len + additional >= *size)
//     {
//         *size *= 2;
//         new_buffer = malloc(*size);
//         if (!new_buffer)
//             exit_error("malloc failed");
//         ft_memcpy(new_buffer, *buffer, *len);
//         free(*buffer);
//         *buffer = new_buffer;
//     }
// }

// void detect_pattern(char **ps, char *es, char *pattern, size_t *pattern_len)
// {
//     *pattern_len = 0;
//     while (*ps < es && !ft_strchr(WHITESPACE, **ps))
//     {
//         if (*pattern_len + 1 >= 256)
//             exit_error("Pattern too long");
//         pattern[(*pattern_len)++] = **ps;
//         (*ps)++;
//     }
//     pattern[*pattern_len] = '\0';
// }

// int process_directory(const char *path, const char *pattern, char **buffer, size_t *len, size_t *size)
// {
//     struct dirent *entry;
//     int expanded = 0;

//     DIR *dir = opendir(path);
//     if (!dir)
//         exit_error("opendir failed");


//     while ((entry = readdir(dir)) != NULL)
//     {
//         if (match_pattern(entry->d_name, pattern))
//         {
//             size_t entry_len = ft_strlen(entry->d_name);
//             ensure_buffer_capacity(buffer, len, entry_len + 2, size);
//             ft_memcpy(*buffer + *len, entry->d_name, entry_len);
//             *len += entry_len;
//             (*buffer)[(*len)++] = ' ';
//             expanded = 1;
//         }
//     }

//     closedir(dir);
//     return expanded;
// }


// void copy_literal_pattern(const char *pattern, size_t pattern_len, char **buffer, size_t *len, size_t *size)
// {
//     ensure_buffer_capacity(buffer, len, pattern_len + 2, size);
//     ft_memcpy(*buffer + *len, pattern, pattern_len);
//     *len += pattern_len;
//     (*buffer)[(*len)++] = ' ';
// }
// void finalize_buffer(char **buffer, size_t *len)
// {
//     if (*len > 0 && (*buffer)[*len - 1] == ' ')
//         (*len)--;

//     (*buffer)[*len] = '\0';
// }

// void expand_wildcards_buff(char **ps, char **es)
// {
//     char *new_buffer;
//     size_t new_size;
//     size_t len;
//     size_t pattern_len;
//     char pattern[256];
//     int expanded;

//     new_buffer = malloc(256);
//     if (!new_buffer)
//         exit_error("malloc failed");
//     new_size = 256;
//     len = 0;
//     while (*ps < *es)
//     {
//         skip_whitespace(ps, *es);
//         if (*ps >= *es)
//             break;
//         pattern_len = 0;
//         expanded = 0;
//         detect_pattern(ps, *es, pattern, &pattern_len);
//         expanded = process_directory(".", pattern, &new_buffer, &len, &new_size);
//         if (!expanded)
//             copy_literal_pattern(pattern, pattern_len, &new_buffer, &len, &new_size);
//     }

//     finalize_buffer(&new_buffer, &len);
//     *ps = new_buffer;
//     *es = new_buffer + len;
// }

///////////////////////////////////////////////////////////////////////////////

// void expand_wildcards_buff(char **ps, char **es)
// {
//     DIR             *dir;
//     struct dirent   *entry;
//     char            *new_buffer;
//     size_t          new_size = 256;
//     size_t          len = 0;
//     size_t          entry_len;
//     char            pattern[256];
//     size_t          pattern_len = 0;
//     int             expanded;
//   //  char            *start = *ps;

//     new_buffer = malloc(new_size);
//     if (!new_buffer)
//         exit_error("malloc failed");

//     while (*ps < *es)
//     {
//         skip_whitespace(ps, *es);
//         if (*ps >= *es)
//             break;

//         // Inicializar el estado para cada patrón
//         expanded = 0;
//         pattern_len = 0;

//         // Detectar patrón (hasta el siguiente espacio o carácter especial)
//         while (*ps < *es && !ft_strchr(WHITESPACE, **ps))
//         {
//             if (pattern_len + 1 >= sizeof(pattern))
//             {
//                 printf("Error: patrón demasiado largo.\n");
//                 free(new_buffer);
//                 return;
//             }
//             pattern[pattern_len++] = **ps;
//             (*ps)++;
//         }
//         pattern[pattern_len] = '\0';

//         // Abrir directorio y buscar coincidencias
//         dir = opendir(".");
//         if (!dir)
//         {
//             free(new_buffer);
//             exit_error("opendir failed");
//         }

//         while ((entry = readdir(dir)) != NULL)
//         {
//             if (match_pattern(entry->d_name, pattern))
//             {
//                 entry_len = ft_strlen(entry->d_name);
//                 if (len + entry_len + 2 >= new_size)
//                 {
//                     new_size *= 2;
//                     new_buffer = realloc(new_buffer, new_size);
//                     if (!new_buffer)
//                         exit_error("realloc failed");
//                 }
//                 ft_memcpy(new_buffer + len, entry->d_name, entry_len);
//                 len += entry_len;
//                 new_buffer[len++] = ' '; // Separar nombres con espacio
//                 expanded = 1;
//             }
//         }
//         closedir(dir);

//         // Si no hubo expansión, copiar el patrón literal
//         if (!expanded)
//         {
//             entry_len = ft_strlen(pattern);
//             if (len + entry_len + 2 >= new_size)
//             {
//                 new_size *= 2;
//                 new_buffer = realloc(new_buffer, new_size);
//                 if (!new_buffer)
//                     exit_error("realloc failed");
//             }
//             ft_memcpy(new_buffer + len, pattern, entry_len);
//             len += entry_len;
//             new_buffer[len++] = ' ';
//         }
//     }

//     // Quitar el último espacio extra
//     if (len > 0 && new_buffer[len - 1] == ' ')
//         len--;

//     new_buffer[len] = '\0';

//     // Actualizar punteros
//     *ps = new_buffer;
//     *es = new_buffer + len;
// }
