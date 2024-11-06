/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:19:05 by mac               #+#    #+#             */
/*   Updated: 2024/11/06 15:00:36 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../include/minishell.h"

static void	suppress_output(void)
{
	struct termios	termios_path;

	if (tcgetattr(0, &termios_path) != 0)
		perror("Minishell: tcgetattr");
	termios_path.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_path) != 0)
		perror("Minishell: tcsetattr");
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	handle_signals(void)
{
	suppress_output();
	signal(SIGUSR2, handle_eof);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

// void	handle_sigint(int sig)
// {
// 	static int	sigint_count = 0;

// 	if (sig == SIGINT)
// 	{
// 		sigint_count++;
// 		if (sigint_count == 1)
// 		{
// 			printf("\n%s", PROMPT);
// 			fflush(stdout);
// 		}
// 		else if (sigint_count >= 2)
// 		{
// 			printf("\b\b  \b\b");
// 			printf("\n%s", PROMPT);
// 			fflush(stdout);
// 		}
// 	}
// }

// void	handle_eof(int sig)
// {
// 	if (sig == SIGUSR2)
// 		exit(0);
// }

// void	handle_sigquit(int sig)
// {
// 	static int	sigquit_count = 0;

// 	if (sig == SIGQUIT)
// 	{
// 		sigquit_count++;
// 		if (sigquit_count == 1)
// 		{
// 			printf("\b\b  \b\b");
// 		}
// 		else
// 			write(STDOUT_FILENO, "\b\b  \b\b", 6);
// 	}
// }

// void	handle_signals(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_eof;
// 	struct sigaction	sa_quit;

// 	ft_memset(&sa_int, 0, sizeof(sa_int));
// 	ft_memset(&sa_eof, 0, sizeof(sa_eof));
// 	ft_memset(&sa_quit, 0, sizeof(sa_quit));
// 	sa_int.sa_handler = &handle_sigint;
// 	sa_eof.sa_handler = &handle_eof;
// 	sa_quit.sa_handler = &handle_sigquit;
// 	sa_int.sa_flags = SA_RESTART;
// 	sa_eof.sa_flags = SA_RESTART;
// 	sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa_int, NULL);
// 	sigaction(SIGUSR2, &sa_eof, NULL);
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }
