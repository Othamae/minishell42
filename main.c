/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashobajo <ashobajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:01:16 by ashobajo          #+#    #+#             */
/*   Updated: 2024/10/08 15:34:49 by ashobajo         ###   ########.fr       */
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

int avsh_echo(char **args);
int avsh_cd(char **args);
int avsh_pwd(char **args);
int avsh_export(char **args);
int avsh_unset(char **args);
int avsh_env(char **args);
int avsh_exit(char **args);
int	avsh_launch(char **argv);

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


int	avsh_launch(char **argv)
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
			line = readline("avsh> ");
			if (line == NULL)
			{
				break;
			}
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

			// avsh_launch(args);

			free(line);
		}
	}
	else
	{
		printf("usage: ./minishell\n");
	}

	return (0);
}
