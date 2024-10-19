/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:19:05 by mac               #+#    #+#             */
/*   Updated: 2024/10/18 08:06:46 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_sigint(int sig)
{
	static int sigint_count = 0;

	if (sig == SIGINT)
	{
		sigint_count++;

		if (sigint_count == 1)
		{
			printf("\n%s", PROMPT);
			fflush(stdout);
		}
		else if (sigint_count >= 2)
		{
			printf("\b\b  \b\b");
			printf("\n%s", PROMPT);
			fflush(stdout);
		}
	}
}

void handle_eof(int sig)
{
	if (sig == SIGUSR2) {
		exit(0);
	}
}

void handle_sigquit(int sig)
{
	static int sigquit_count = 0;

	if (sig == SIGQUIT)
	{
		sigquit_count++;

		if (sigquit_count == 1)
		{
			printf("\b\b  \b\b");
		}
		else
		{
			fflush(stdout);
			printf("\b\b  \b\b");
		}
	}
}

void handle_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_eof;
	struct sigaction sa_quit;

	sa_int.sa_handler = &handle_sigint;
	sa_eof.sa_handler = &handle_eof;
	sa_quit.sa_handler = &handle_sigquit;

	sa_int.sa_flags = SA_RESTART;
	sa_eof.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGUSR2, &sa_eof, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
