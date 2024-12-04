/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:19:05 by mac               #+#    #+#             */
/*   Updated: 2024/12/04 11:03:46 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	g_signal_received = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	default_signals(void)
{
	suppress_output();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	suppress_output();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
