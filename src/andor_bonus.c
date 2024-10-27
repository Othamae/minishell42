/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/27 21:10:02 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_and_or(t_clist *lcmd, int *status)
{
	if (fork1() == 0)
	{
		runcmd(lcmd->left);
		exit(0);
	}
	wait(status);
	if (lcmd->base.type == AND_T)
	{
		if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right);
			wait(status);
		}
	}
	else if (lcmd->base.type == OR_T)
	{
		if (!WIFEXITED(*status) || WEXITSTATUS(*status) != 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right);
			wait(status);
		}
	}
	*status = WEXITSTATUS(*status);
}

void	handle_subshell(t_subshell *subcmd, int *status)
{
	if (fork1() == 0)
	{
		runcmd(subcmd->subcmd);
		exit(0);
	}
	else
	{
		wait(status);
		*status = WEXITSTATUS(*status);
	}
}
