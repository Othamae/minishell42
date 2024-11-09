/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/06 20:38:49 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_and_or(t_clist *lcmd, int *status, t_context *context)
{
	if (fork1() == 0)
	{
		runcmd(lcmd->left, context);
		exit(0);
	}
	wait(status);
	if (lcmd->base.type == AND_T)
	{
		if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right, context);
			wait(status);
		}
	}
	else if (lcmd->base.type == OR_T)
	{
		if (!WIFEXITED(*status) || WEXITSTATUS(*status) != 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right, context);
			wait(status);
		}
	}
	*status = WEXITSTATUS(*status);
}

void	handle_subshell(t_subshell *subcmd, int *status, t_context *context)
{
	if (fork1() == 0)
	{
		runcmd(subcmd->subcmd, context);
		exit(0);
	}
	else
	{
		wait(status);
		*status = WEXITSTATUS(*status);
	}
}
