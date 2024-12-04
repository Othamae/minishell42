/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_context.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:31:00 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/04 09:05:02 by vconesa-         ###   ########.fr       */
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
	context->env[i] = NULL;
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

void	init_buff(t_wildbuff *buf, int argc, char **argv)
{
	buf->buffer = NULL;
	(void)argc;
	(void)argv;
}

void	check_sigint(t_context *context)
{
	if (g_signal_received == SIGINT)
	{
		context->last_status = 130;
		g_signal_received = 0;
	}
}
