/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/19 10:56:50 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	getcmd(char *buff, int nbuf)
{
	char	*input;

	ft_memset(buff, 0, nbuf);
	input = readline(PROMPT);
	if (!input)
		return -1;
	ft_strlcpy(buff, input, nbuf);
	if(buff[0] == 0) // EOF
		return -1;
	free(input);
	return 0;
}

void runcmd(t_cmd *cmd)
{

	int p[2];
	extern char **environ;
	t_exec *ecmd;
	t_pipe *pcmd;
	t_redir *rcmd;

	if(cmd == 0)
		exit(1);


	if(cmd->type == EXEC_T)
	{
		ecmd = (t_exec *)cmd;
		if(ecmd->argv[0] == 0)
			exit(1);
		execve(ecmd->argv[0], ecmd->argv, environ);
		printf("exec %s failed\n", ecmd->argv[0]);
	}
	else if(cmd->type == REDIR_T)
	{
		rcmd = (t_redir *)cmd;
		close(rcmd->fd);
		if(open(rcmd->file, rcmd->mode, 0664) < 0)
		{
			printf("open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd);

	}
	else if(cmd->type == PIPE_T)
	{
		pcmd = (t_pipe *)cmd;
		if(pipe(p) < 0)
			exit_error("pipe");
		if(fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if(fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else
		exit_error("runcmd error");
	exit(0);

}

int	main(int argc, char **argv)
{
	(void) argv;
	static char	buff[100];
	int			fd;

	if (argc == 1)
	{
		while((fd = open(PROMPT, O_RDWR)) >= 0)
		{
			if (fd >= 3)
			{
				close(fd);
				break;
			}
		}
		handle_signals();
		while (1)
		{
			while((getcmd(buff,sizeof(buff)) >= 0))
			{
				add_history(buff);
				//we should check first if no token in the line the do builting
				if (do_builtins(buff))
					continue;
				if(fork1() == 0)
				{
					runcmd(parsecmd(buff));
				}

				wait(NULL);
			}
			// exit(1);
		}
	}
	else
		{
			printf("usage: ./minishell\n");
		}
	return (0);
}


// int main(void)
// {
// 	static char	buff[100];
// 	int			fd;

// 	handle_signals();

// 	while((fd = open(PROMPT, O_RDWR)) >= 0)
// 	{
// 		if (fd >= 3)
// 		{
// 			close(fd);
// 			break;
// 		}
// 	}

// 	while((getcmd(buff,sizeof(buff)) >= 0))
// 	{

// 		add_history(buff);
// 		if (do_builtins(buff))
// 			continue;
// 		if(fork1() == 0)
// 		{
// 			runcmd(parsecmd(buff));
// 		}
// 		wait(0);
// 	}
// 	exit(1);
// }
