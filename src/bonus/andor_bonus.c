/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/24 13:00:11 by vconesa-         ###   ########.fr       */
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
		runcmd(subcmd->subcmd, context);
		exit(context->last_status);
	}
	else
	{
		wait(status);
		*status = WEXITSTATUS(*status);
		context->last_status = *status;
	}
}
