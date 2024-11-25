/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_context.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:31:00 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/25 19:50:42 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_context(char **env, t_context *context)
{
	int	i;
	int	count;

	count = 0;
	while (env[count])
		count++;
	context->env = safe_malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		context->env[i] = ft_strdup(env[i]);
		i++;
	}
	context->env[i] = '\0';
	context->last_status = 0;
	context->is_pipe_child = 0;
	context->redir_handled = 0;
}

void	free_env(t_context *context)
{
	int	i;

	i = 0;
	while (context->env[i] != NULL)
	{
		free(context->env[i]);
		i++;
	}
	free(context->env);
}
