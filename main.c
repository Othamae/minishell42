/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:01:16 by ashobajo          #+#    #+#             */
/*   Updated: 2024/10/09 05:39:02 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

int vash_echo(char **args);
int vash_cd(char **args);
int vash_pwd(char **args);
int vash_export(char **args);
int vash_unset(char **args);
int vash_env(char **args);
int	vash_launch(char **argv);

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}


char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str = NULL;
	char		*token;
	int			i = 0;
	int			start = 0;
	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	if (saved_str[start] == '\0')
	{
		saved_str = NULL;
		return (NULL);
	}
	while (saved_str[start] != '\0' && ft_strchr(delim, saved_str[start]) != NULL)
		start++;
	i = start;
	while (saved_str[i] != '\0' && ft_strchr(delim, saved_str[i]) == NULL)
		i++;
	token = &saved_str[start];
	if (saved_str[i] != '\0')
	{
		saved_str[i] = '\0';
		saved_str = &saved_str[i + 1];
	}
	else
		saved_str = NULL;
	return (token);
}


int	vash_launch(char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("type in a valid command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		{
			wait(NULL);
		}

	else {
		perror("a forking error occured");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int	main(int argc, char **argv)
{
	char *line;
	char *args[64];
	char *token;
	int i;

	if (argc == 1)
	{
		while (1)
		{
			line = readline("vash% ");
			if (line == NULL)
				break;
			if (line[0] != '\0')
			{
				add_history(line);
			}
			i = 0;
			token = ft_strtok(line, " ");
			while (token != NULL)
			{
				args[i++] = token;
				token = ft_strtok(NULL, " ");
			}
			args[i] = NULL;
			if (args[0] == NULL)
			{
				free(line);
				continue;
			}
			if (strcmp(args[0], "exit") == 0)
			{
				free(line);
				break;
			}
			if (strcmp(args[0], "cd") == 0)
				vash_cd(args);
			if (strcmp(args[0], "echo") == 0)
				vash_echo(args);
			if (strcmp(args[0], "pwd") == 0)
				vash_pwd(args);
			if (strcmp(args[0], "env") == 0)
				vash_env(args);
			// vash_launch(args);
			free(line);
		}
	}
	else
	{
		printf("usage: ./minishell\n");
	}
	return (0);
}

int vash_cd(char **args)
{
	if (chdir(args[1]) < 0)
	{
		printf("Error: invalid pathname\n");
		return (1);
	}
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vash_echo(char **args)
{
	char	*new_str;
	char	*old_str;
	int		i = 1;
	int		j = 0;
	int		no_newline = 0;

	if (args[1] == NULL)
	{
		printf("%s\n", "   ");
		return (0);
	}
	if (strcmp(args[1], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}

	old_str = args[i];
	if (old_str == NULL)
	{
		if (no_newline)
			printf("%s", " ");
		else
			printf("\n");
		return (0);
	}
	new_str = (char *)malloc(strlen(old_str) + 1);
	if (new_str == NULL)
	{
		printf("error allocating new string");
		return (0);
	}
	if ((old_str[0] == 34 && old_str[strlen(old_str) - 1] == 34) ||
		(old_str[0] == 39 && old_str[strlen(old_str) - 1] == 39))
	{
		while (old_str[i] != old_str[strlen(old_str) - 1])
			new_str[j++] = old_str[i++];
		new_str[j] = '\0';
	}
	else
		new_str = old_str;
	if (no_newline)
		printf("%s", new_str);
	else
		printf("%s\n", new_str);

	if (new_str != old_str)
		free(new_str);

	return (0);
}


int vash_pwd(char **args)
{
	char *pwd = getenv("PWD");
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
	}
	return 0;
}

int vash_env(char **args)
{
	extern char **environ;
	char **env;

	env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return 0;
}
