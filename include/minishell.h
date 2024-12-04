/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:14:26 by vconesa-          #+#    #+#             */
/*   Updated: 2024/12/04 11:02:51 by vconesa-         ###   ########.fr       */
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
# include <signal.h>
# include <glob.h>
# include <termios.h>
# include <dirent.h>
// # include <linux/limits.h>

# define EXEC_T 1
# define REDIR_T 2
# define PIPE_T 3
# define HERDOC_T 4
# define AND_T 5
# define OR_T 6
# define SUBSHELL_T 7

# define MAXARGS 50
# define PROMPT	"\001\e[45m\002>>> \001\e[0m\e[33m\002Minishell>$ \001\e[0m\002"

# define WHITESPACE " \t\r\v"
# define SYMBOLS "<|>&()\"'"
# define PERMISSIONS 0664
# define MAX_BUFFER_SIZE 4064
# define PATH_SEPARATOR ":"
# define MAX_PATH_LENGTH 512

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
# define D_QUOTE '"'
# define S_QUOTE 39

extern int	g_signal_received;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_wildbuff
{
	char	*buffer;
	size_t	len;
	size_t	size;
}	t_wildbuff;

typedef struct s_exec
{
	t_cmd		base;
	char		*argv[MAXARGS];
	char		*eargv[MAXARGS];
	t_wildbuff	buff_exp;
}	t_exec;

typedef struct s_redir_info
{
	int	mode;
	int	fd;
}	t_redir_info;

typedef struct s_redir
{
	t_cmd			base;
	char			*file;
	char			*efile;
	t_redir_info	info;
	t_cmd			*cmd;
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
	t_cmd	*subcmd;
}	t_subshell;

typedef struct s_context
{
	int		last_status;
	int		is_pipe_child;
	int		redir_handled;
	char	**env;
}	t_context;

typedef struct s_qsort
{
	char	*array;
	char	*left;
	char	*right;
	char	*pivot;
}	t_qsort;

// utils.c
int		fork1(void);
void	exit_error(char *s);
int		count_char(const char *str, char c);
char	*ft_strstr(const char *haystack, const char *needle);
int		has_unclosed_quotes(const char *s);

// utils_2.c
char	*ft_strtok(char *str, const char *delim);
int		only_spaces(char *str);
int		is_builtin(char *cmd);

// parse
t_cmd	*parsecmd(char *s, t_wildbuff *buf);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseline(char **ps, char *es);

// parse_utils
t_cmd	*handle_parseredirs(t_cmd *cmd, char *q, char *eq, int tok);
t_cmd	*handle_parseexec(char **ps, char *es, t_exec *cmd, t_cmd *ret);

// parse_utils_2
void	handle_d_quotes(char *s, char **es);

// nulterminate
t_cmd	*nulterminate(t_cmd *cmd);

// inits
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, t_redir_info info);
t_cmd	*heredoccmd(char *delim, t_cmd *subcmd);
t_cmd	*listcmd(t_cmd *left, t_cmd *right, int type);
t_cmd	*subshellcmd(t_cmd *subcmd);

// token
int		find_next_token(char **ps, char *es, char *tokens);
int		get_token(char **ps, char *es, char **q, char **eq);

// token utils
void	skip_whitespace(char **s, char *es);

// builtins
int		vash_echo(char **args, t_context *context);
int		vash_cd(char **args, t_context *context);
int		vash_env(t_context *context);
int		handle_builtins(char **args, t_context *context, t_cmd *cmd);
int		ft_pwd(void);
int		vash_unset(char **args, t_context *context);
int		vash_export(char **args, t_context *context);

// exec
void	runcmd(t_cmd *cmd, t_context *context);
void	handle_herdoc(t_herdoc *hcmd, t_context *context);
void	handle_pipe(t_pipe *pcmd, t_context *context);
void	handle_redir(t_redir *rcmd, t_context *context);
void	exec_pipe_child(t_cmd *cmd, int p[2], int is_left, t_context *context);
void	handle_and_or(t_clist *lcmd, t_context *context);
int		handle_exec(t_exec *ecmd, t_context *context);
void	handle_subshell(t_subshell *subcmd, int *status, t_context *context);

// signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_signals(void);
void	ignore_signals(void);
void	default_signals(void);
void	handle_sigint_herdoc(int sig);
void	suppress_output(void);

// context
void	init_context(char **env, t_context *context);
void	free_env(t_context *context);
void	init_buff(t_wildbuff *buf, int argc, char **argv);
void	check_sigint(t_context *context);

// free_cmd
void	free_cmd(t_cmd *cmd);

// echo
int		process_args(char *old_str, int no_newline);
void	*safe_malloc(size_t bytes);
void	print_str(char *old_str, char *new_str, int no_newline);
void	handle_s_quoted_env(char *arg, char *old_str, int *j,
			t_context *context);
void	handle_d_quoted_env(char *arg, char *old_str, int *j,
			t_context *context);
void	handle_env_var(char *arg, char *old_str, int *j, t_context *context);
char	*ft_getenv(const char *name, char **env);

// export_env_utils.c
void	print_sorted_env(t_context *context);
char	**copy_environ(int *count, t_context *context);
int		ft_setenv(char *name, char *value, t_context *context);

// ft_qsort
int		compare_strings(const void *a, const void *b);
void	ft_qsort(void *base, size_t nitems, size_t size,
			int (*compar)(const void *, const void *));

// wildcards
void	expand_wildcards_buff(char **ps, char **es, t_wildbuff *buf);

// wildcards_utils
void	set_values(int *i, int i_value, int *j, int j_value);
void	ensure_buffer_capacity(t_wildbuff *buf, size_t additional);
void	finalize_buffer(t_wildbuff *buf);
void	copy_literal_pattern(char *pattern, size_t patt_len, t_wildbuff *buf);

#endif
