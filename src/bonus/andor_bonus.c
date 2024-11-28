/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/28 14:40:42 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_and_or(t_clist *lcmd, int *status, t_context *context)
{
	runcmd(lcmd->left, context);
	*status = context->last_status;
	if (lcmd->base.type == AND_T)
	{
		if (*status == 0)
			runcmd(lcmd->right, context);
	}
	else if (lcmd->base.type == OR_T)
	{
		if (*status != 0)
			runcmd(lcmd->right, context);
	}
	*status = context->last_status;
}

void	handle_subshell(t_subshell *subcmd, int *status, t_context *context)
{
	if (fork1() == 0)
	{
		default_signals();
		runcmd(subcmd->subcmd, context);
		exit(context->last_status);
	}
	else
	{
		ignore_signals();
		wait(status);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		*status = WEXITSTATUS(*status);
		context->last_status = *status;
	}
}
