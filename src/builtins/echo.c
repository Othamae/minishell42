/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:00 by mac               #+#    #+#             */
/*   Updated: 2024/11/18 18:40:14 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_no_args(char **args)
{
	if (args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	return (0);
}

static void	process_arguments(char **args, char *old_str, int *i, int *j)
{
	while (args[*i] != NULL)
	{
		if ((args[*i][0] == '$') || (args[*i][1] == '$'
			&& (args[*i][0] == 34 && (args[*i][ft_strlen(args[*i]) - 1] == 34)))
			|| (args[*i][2] == '$' && (args[*i][0] == 34
			&& (args[*i][ft_strlen(args[*i]) - 1] == 34))))
		{
			if (args[*i][0] == '$')
				handle_env_var(args[*i], old_str, j);
			else if (args[*i][1] == '$'
			&& (args[*i][0] == 34 && (args[*i][ft_strlen(args[*i]) - 1] == 34)))
				handle_double_quoted_env_var(args[*i], old_str, j);
			else
				handle_single_quoted_env_var(args[*i], old_str, j);
		}
		else
		{
			while (*(args[*i]) != '\0')
				old_str[(*j)++] = *((args[*i])++);
		}
		if (args[*i + 1] != NULL)
			old_str[(*j)++] = ' ';
		(*i)++;
	}
}

int	process_args(char *old_str, int no_newline)
{
	int		j;
	int		i;
	char	*new_str;

	j = 0;
	i = 1;
	if (old_str[j] == '\0')
		handle_null(no_newline);
	new_str = safe_malloc(strlen(old_str) + 1);
	if ((old_str[0] == 34 && old_str[strlen(old_str) - 1] == 34)
		|| (old_str[0] == 39 && old_str[strlen(old_str) - 1] == 39))
	{
		while (old_str[i] != old_str[strlen(old_str) - 1])
			new_str[j++] = old_str[i++];
		new_str[j] = '\0';
	}
	else
		strcpy(new_str, old_str);
	print_str(old_str, new_str, no_newline);
	return (0);
}

static void	echo_status(char **args, t_context *context)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "$?", 3) == 0)
			ft_printf("%d", context->last_status);
		else
			ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	exit(0);
}

int	vash_echo(char **args, t_context *context)
{
	char	old_str[1024];
	int		i;
	int		j;
	int		no_newline;

	i = 1;
	j = 0;
	no_newline = 0;
	handle_no_args(args);
	if (strncmp(args[1], "-n", 3) == 0)
	{
		no_newline = 1;
		i++;
	}
	if (ft_strncmp(args[1], "$?", 3) == 0)
		echo_status(args, context);
	process_arguments(args, old_str, &i, &j);
	old_str[j] = '\0';
	process_args(old_str, no_newline);
	return (0);
}