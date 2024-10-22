/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/22 13:35:08 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_and_or(t_clist *lcmd, int *status)
{
	if (fork1() == 0)
		runcmd(lcmd->left);
	wait(status);
	if (lcmd->base.type == AND_T)
	{
		if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right);
			wait(0);
		}
	}
	else if (lcmd->base.type == OR_T)
	{
		if (!WIFEXITED(*status) || WEXITSTATUS(*status) != 0)
		{
			if (fork1() == 0)
				runcmd(lcmd->right);
			wait(0);
		}
	}
}
