/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/29 17:45:47 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_next_cmd(t_clist *lcmd, t_context *context)
{
	t_clist	*right;

	right = (t_clist *)lcmd->right;
	if (right)
		runcmd(right->right, context);
}

void	handle_and_or(t_clist *lcmd, t_context *context)
{
	runcmd(lcmd->left, context);
	if (lcmd->base.type == AND_T)
	{
		if (context->last_status == 0)
			runcmd(lcmd->right, context);
		else if (lcmd->right->type != EXEC_T && lcmd->right->type != PIPE_T
			&& lcmd->right->type != AND_T)
			check_next_cmd(lcmd, context);
	}
	else if (lcmd->base.type == OR_T)
	{
		if (context->last_status != 0)
			runcmd(lcmd->right, context);
		else if (lcmd->right->type != EXEC_T && lcmd->right->type != PIPE_T
			&& lcmd->right->type != OR_T)
			check_next_cmd(lcmd, context);
	}
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
