/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:59:48 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 11:24:35 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_path(char *s, char **argv, char **environ)
{
	char	*path_env;
	char	*path_token;
	char	f_path[MAX_PATH_LENGTH];
	size_t	tok_len;
	size_t	cmd_len;

	path_env = getenv("PATH");
	if (path_env == NULL)
		exit_error("Error: PATH not configured\n");
	path_token = ft_strtok(path_env, PATH_SEPARATOR);
	while (path_token != NULL)
	{
		tok_len = ft_strlen(path_token);
		cmd_len = ft_strlen(s);
		if (tok_len + 1 + cmd_len < MAX_PATH_LENGTH)
		{
			ft_strlcpy(f_path, path_token, MAX_PATH_LENGTH);
			f_path[tok_len] = '/';
			f_path[tok_len + 1] = '\0';
			ft_strlcpy(f_path + tok_len + 1, s, MAX_PATH_LENGTH - tok_len - 1);
			execve(f_path, argv, environ);
		}
		path_token = ft_strtok(NULL, PATH_SEPARATOR);
	}
	return (-1);
}

int	handle_exec(t_exec *ecmd, t_context *context)
{
	extern char	**environ;

	if (handle_builtins(ecmd->argv, context))
		return (0);
	if (ecmd->argv[0] == 0)
	{
		context->last_status = 1;
		return (1);
	}
	if (ft_strchr(ecmd->argv[0], '/') != NULL)
		execve(ecmd->argv[0], ecmd->argv, environ);
	else
		handle_path(ecmd->argv[0], ecmd->argv, environ);
	ft_printf("exec %s failed\n", ecmd->argv[0]);
	context->last_status = 127;
	exit(context->last_status);
	return (context->last_status);
}
