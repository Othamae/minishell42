/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/13 15:50:27 by vconesa-         ###   ########.fr       */
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
	t_herdoc *hcmd;

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
	else if(cmd->type == HERDOC_T)
	{
		hcmd =(t_herdoc *)cmd;
        if (pipe(p) < 0)
            exit_error("pipe");
		char *line;
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				break;
			if (ft_strncmp(line, hcmd->delim, ft_strlen(hcmd->delim)) == 0)
			{
				free(line);
				break;
			}
			size_t len = ft_strlen(line);
			if (write(p[1], line, len) != (ssize_t)len)
			{
				perror("write");
				free(line);
				close(p[1]);
				exit(EXIT_FAILURE);
			}
			if (write(p[1], "\n", 1) != 1)
			{
				perror("write");
				free(line);
				close(p[1]);
				exit(EXIT_FAILURE);
			}
			
			free(line);
		}
		close(p[1]);
		if (fork1() == 0)
		{
			close(0);        
			dup(p[0]);     
			close(p[0]); 			
			runcmd(hcmd->right);
		}
		close(p[0]);
		wait(0);
	}
	else
		exit_error("runcmd error");
	exit(0);

}


int main(void)
{
	static char	buff[100];
	int			fd;

	while((fd = open(PROMPT, O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}
	
	while((getcmd(buff,sizeof(buff)) >= 0))
	{

		add_history(buff);
		if (do_builtins(buff))
			continue;
		if(fork1() == 0)
		{
			runcmd(parsecmd(buff));
		}
		wait(0);
	}
	exit(1);

}
