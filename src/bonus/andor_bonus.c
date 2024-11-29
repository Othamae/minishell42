/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:01:50 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/29 09:50:27 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_and_or(t_clist *lcmd, int *status, t_context *context)
{
	printf("AND_OR, lcmd->base.type = %d\n", lcmd->base.type);
	printf("lcmd->left->type = %d, lcmd->right->type = %d\n", lcmd->left->type, lcmd->right->type);
	 t_exec *current_cmd = (t_exec *)lcmd->left;
		printf("LEFT = %s, RIGHT = %s\n", current_cmd->argv[0], ((t_exec *)lcmd->right)->argv[0]);


	runcmd(lcmd->left, context);
	printf("Despues de ejecutar el comando context->last_status= %d\n", context->last_status);
	
	*status = context->last_status;
	if (lcmd->base.type == AND_T)
	{
	 current_cmd = (t_exec *)lcmd->right;
		printf("AND_T right= %s\n", current_cmd->argv[0]);
		if (*status == 0)
			runcmd(lcmd->right, context);
		
	}
	else if (lcmd->base.type == OR_T)
	{
		 current_cmd = (t_exec *)lcmd->right;
		printf("OR_T right = %s\n", current_cmd->argv[0]);
		if (*status != 0)
			runcmd(lcmd->right, context);
	}


	 current_cmd = (t_exec *)lcmd->right;


	
	printf("context->last_status = %d\n", context->last_status);
	printf("current_cmd = %s\n", current_cmd->argv[0]);
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
