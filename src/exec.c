/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:59:48 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/04 10:25:34 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_path(char *s, char **argv, char **env)
{
	char	*path_env;
	char	*path_token;
	char	f_path[MAX_PATH_LENGTH];
	size_t	tok_len;
	size_t	cmd_len;

	path_env = ft_getenv("PATH", env);
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
			execve(f_path, argv, env);
		}
		path_token = ft_strtok(NULL, PATH_SEPARATOR);
	}
	return (-1);
}

static int	is_builtin_child(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "setenv", 7) || !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "unsetenv", 9));
}

int	handle_exec(t_exec *ecmd, t_context *context)
{
	if (is_builtin_child(ecmd->argv[0]))
		return (handle_builtins(ecmd->argv, context, (t_cmd *)ecmd));
	if (ecmd->argv[0] == 0)
	{
		context->last_status = 1;
		return (1);
	}
	if (ft_strchr(ecmd->argv[0], '/') != NULL)
		execve(ecmd->argv[0], ecmd->argv, context->env);
	else
		handle_path(ecmd->argv[0], ecmd->argv, context->env);
	ft_printf("exec %s failed\n", ecmd->argv[0]);
	if (g_signal_received == SIGINT)
		context->last_status = 130;
	else
		context->last_status = 127;
	exit(context->last_status);
	return (context->last_status);
}
