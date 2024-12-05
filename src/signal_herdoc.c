/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:37:24 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/05 12:37:45 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint_herdoc(int sig)
{
	g_signal_received = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}

void	suppress_output(void)
{
	struct termios	termios_path;

	if (!isatty(0))
		return ;
	if (tcgetattr(0, &termios_path) != 0)
	{
		perror("Minishell: tcgetattr");
		return ;
	}
	termios_path.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &termios_path) != 0)
		perror("Minishell: tcsetattr");
}
