/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 14:11:37 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	vash_launch(char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("type in a valid command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("a forking error occured");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	handle_builtins(char **args, t_context *context)
{
	if (args[0] == NULL)
		return (0);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		vash_cd(args);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		vash_echo(args, context);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "env", 4) == 0)
		vash_env();
	else if (ft_strncmp(args[0], "export", 7) == 0)
		vash_export(args);
	else if (ft_strncmp(args[0], "setenv", 7) == 0)
		vash_env();
	else if (ft_strncmp(args[0], "unset", 6) == 0
		|| ft_strncmp(args[0], "unsetenv", 9) == 0)
		vash_unset(args);
	else
		return (context->last_status = 0);
	return (context->last_status = 1);
}

//Previous code of handle_builtins -- delete if everything works

//int handle_builtins(char **args)
// {
// 	if (args[0] == NULL)
// 		return 0;
// 	if (ft_strncmp(args[0], "exit", 5) == 0)
// 		exit(0);
// 	else if (ft_strncmp(args[0], "cd", 3) == 0)
// 		vash_cd(args);
// 	else if (ft_strncmp(args[0], "echo", 5) == 0)
// 		vash_echo(args);
// 	else if (ft_strncmp(args[0], "pwd", 4) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(args[0], "env", 4) == 0)
// 		vash_env();
// 	else if (ft_strncmp(args[0], "export", 7) == 0
// 		|| ft_strncmp(args[0], "setenv", 7) == 0)
// 	{
// 		if (args[1] == NULL && ft_strncmp(args[0], "setenv", 7) != 0)
// 			vash_env();
// 		else
// 			vash_export(args);
// 	}
// 	else if (ft_strncmp(args[0], "unset", 6) == 0
// 		|| ft_strncmp(args[0], "unsetenv", 9) == 0)
// 		vash_unset(args);
// 	else
// 		return (0);
// 	return (1);
// }
