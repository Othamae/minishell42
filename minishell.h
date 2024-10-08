/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:14:26 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/08 20:59:54 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXEC_T 1
# define REDIR_T 2
# define PIPET_T 3

# define MAXARGS 10
# define PROMP	"minishell$ "

# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&()"

# define PIPE '|'
# define REDIR_FROM '<'
# define REDIR_TO '>'
# define REDIR_ADD '+'
# define HERE_DOC '-'
# define ENV_VA '$'
# define OTHER 'a'

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	t_cmd	*cmd;
}	t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

//utils.c
int		fork1(void);
void	exit_error(char *s);

// parse
t_cmd *parsecmd(char *s);

#endif
