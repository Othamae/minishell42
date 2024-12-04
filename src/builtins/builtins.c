/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/04 10:27:26 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtins(char **args, t_context *context, t_cmd *cmd)
{
	if (!args[0])
		return (0);
	if (!ft_strncmp(args[0], "exit", 5))
	{
		free_cmd(cmd);
		free_env(context);
		exit(0);
	}
	else if (!ft_strncmp(args[0], "cd", 3))
		return (vash_cd(args, context));
	else if (!ft_strncmp(args[0], "echo", 5))
		return (vash_echo(args, context));
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(args[0], "env", 4))
		return (vash_env(context));
	else if (!ft_strncmp(args[0], "export", 7))
		return (vash_export(args, context));
	else if (!ft_strncmp(args[0], "unset", 6))
		return (vash_unset(args, context));
	return (0);
}
