/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:14:26 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/19 16:18:20 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <linux/limits.h>

# define EXEC_T 1
# define REDIR_T 2
# define PIPE_T 3
# define HERDOC_T 4
# define AND_T 5
# define OR_T 6
# define SUBSHELL_T 7

# define MAXARGS 10
# define PROMPT	"\001\e[45m\002>>> \001\e[0m\e[33m\002Minishell>$ \001\e[0m\002"

# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&()"
# define PERMISSIONS 0664

# define PIPE '|'
# define REDIR_FROM '<'
# define REDIR_TO '>'
# define REDIR_ADD '+'
# define HERE_DOC '-'
# define ENV_VA '$'
# define OTHER 'a'
# define AND '&'
# define OR	'o'
# define OPEN_P '('
# define CLOSE_P ')'

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec
{
	t_cmd	base;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_exec;

typedef struct s_redir
{
	t_cmd	base;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	t_cmd	*cmd;
}	t_redir;

typedef struct s_pipe
{
	t_cmd	base;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_herdoc
{
	t_cmd	base;
	char	*delim;
	t_cmd	*right;
}	t_herdoc;

typedef struct s_clist
{
	t_cmd	base;
	t_cmd	*left;
	t_cmd	*right;
}	t_clist;

typedef struct s_subshell
{
	t_cmd	base;
	t_cmd	*cmd;
}	t_subshell;
//utils.c
int		fork1(void);
void	exit_error(char *s);

// parse
t_cmd	*parsecmd(char *s);

// token
int		find_next_token(char **ps, char *es, char *tokens);
int		get_token(char **ps, char *es, char **q, char **eq);

// builtins
int		vash_echo(char **args);
int		vash_cd(char **args);
int		vash_pwd(void);
int		vash_env(void);
int		vash_launch(char **argv);
int		do_builtins(char *line);

// exec
void	runcmd(t_cmd *cmd);
void	handle_herdoc(t_herdoc *hcmd);
void	handle_pipe(t_pipe *pcmd);
void	handle_redir(t_redir *rcmd);
void	exec_pipe_child(t_cmd *cmd, int p[2], int is_left);

#endif
