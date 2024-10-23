/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:59:48 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/23 15:13:13 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_exec(t_exec *ecmd)
{
	extern char	**environ;

	if (ecmd->argv[0] == 0)
		exit(1);
	execve(ecmd->argv[0], ecmd->argv, environ);
	printf("exec %s failed\n", ecmd->argv[0]);
	exit(1);
}
