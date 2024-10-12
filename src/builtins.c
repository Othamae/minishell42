/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/12 15:31:28 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// find the first occurrence of a substring within a string.
// returns pointer to first character of the first occurrence of the substring
char *ft_strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return (char *)haystack;
	while (*haystack)
	{
		const char *h = haystack;
		const char *n = needle;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return (char *)haystack;

		haystack++;
	}
	return NULL;
}

int count_char(const char *str, char c)
{
	int count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return count;
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

// int	main(int argc, char **argv)
// {
// 	char *line;
// 	char *args[64];
// 	char *token;
// 	int i;

// 	if (argc == 1)
// 	{
// 		while (1)
// 		{
// 			line = readline("vash% ");
// 			if (line == NULL)
// 				break;
// 			if (line[0] != '\0')
// 			{
// 				add_history(line);
// 			}
// 			i = 0;
// 			token = ft_strtok(line, " ");
// 			while (token != NULL)
// 			{
// 				args[i++] = token;
// 				token = ft_strtok(NULL, " ");
// 			}
// 			args[i] = NULL;
// 			if (args[0] == NULL)
// 			{
// 				free(line);
// 				continue;
// 			}
// 			if (strcmp(args[0], "exit") == 0)
// 			{
// 				free(line);
// 				break;
// 			}
// 			if (strcmp(args[0], "cd") == 0)
// 				vash_cd(args);
// 			if (strcmp(args[0], "echo") == 0)
// 				vash_echo(args);
// 			if (strcmp(args[0], "pwd") == 0)
// 				vash_pwd(args);
// 			if (strcmp(args[0], "env") == 0)
// 				vash_env(args);
// 			// vash_launch(args);
// 			free(line);
// 		}
// 	}
// 	else
// 	{
// 		printf("usage: ./minishell\n");
// 	}
// 	return (0);
// }

int vash_cd(char **args)
{
	if (chdir(args[1]) < 0)
	{
		printf("Error: invalid pathname\n");
		return (1);
	}
	return (0);
}

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
	if (ft_strncmp(args[1], "-n", 3) == 0)
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
	new_str = (char *)malloc(ft_strlen(old_str) + 1);
	if (new_str == NULL)
	{
		printf("error allocating new string");
		return (0);
	}
	if ((old_str[0] == 34 && old_str[ft_strlen(old_str) - 1] == 34) ||
		(old_str[0] == 39 && old_str[ft_strlen(old_str) - 1] == 39))
	{
		while (old_str[i] != old_str[ft_strlen(old_str) - 1])
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


int		ft_pwd(void)
{
	char	cwd[PATH_MAX]; //4096

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}

int vash_pwd(void)
{
	char *pwd = getenv("PWD");
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
	}
	return 0;
}

int vash_export(char **args)
{
	extern char **environ;
	int i = 0;
	char *new_exp;
	char *equal_sign;
	char *value_part;
	int len = ft_strlen(args[1]);

	if (ft_strstr(args[1], "==") != NULL)
	{
		printf("Error: invalid format, '==' found\n");
		return 1;
	}
	if (count_char(args[1], '\'') > 2 || count_char(args[1], '"') > 2)
	{
		printf("Error: invalid format, quotes appear too many times\n");
		return 1;
	}
	equal_sign = strchr(args[1], '=');

	if (equal_sign == NULL)
	{
		new_exp = malloc(len + 1);
		if (!new_exp)
		{
			perror("Error: memory allocation failed");
			return 1;
		}
		strcpy(new_exp, args[1]);

		while (environ[i] != NULL)
		{
			if (ft_strncmp(environ[i], new_exp, len) == 0 && environ[i][len] == '\0')
			{
				return 0;
			}
			i++;
		}

		environ[i] = new_exp;
		environ[i + 1] = NULL;

		return 0;
	}
	new_exp = malloc(len + 1);
	if (!new_exp)
	{
		perror("Error: memory allocation failed");
		return 1;
	}
	value_part = equal_sign + 1;
	if ((*value_part == '\'' && value_part[ft_strlen(value_part) - 1] == '\'') ||
		(*value_part == '"' && value_part[ft_strlen(value_part) - 1] == '"'))
	{
		value_part[ft_strlen(value_part) - 1] = '\0';
		value_part++;
	}
	strncpy(new_exp, args[1], equal_sign - args[1] + 1);
	strcpy(new_exp + (equal_sign - args[1] + 1), value_part);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], new_exp, equal_sign - args[1]) == 0)
		{
			environ[i] = new_exp;
			return 0;
		}
		i++;
	}
	environ[i] = new_exp;
	environ[i + 1] = NULL;
	return 0;
}


int vash_env(void)
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

int vash_unset(char **args)
{
	extern char **environ;
	int i, j, k;
	int len;

	if (args[1] == NULL)
	{
		printf("Error: expected argument to unset\n");
		return 1;
	}
	k = 1;
	while (args[k] != NULL)
	{
		i = 0;
		len = ft_strlen(args[k]);
		while (environ[i] != NULL)
		{
			if (ft_strncmp(environ[i], args[k], len) == 0 && environ[i][len] == '=')
			{
				j = i;
				while (environ[j] != NULL)
				{
					environ[j] = environ[j + 1];
					j++;
				}
				break;
			}
			i++;
		}
		k++;
	}
	return 0;
}

int do_builtins(char *buff)
{
	int i;
	char *token;
	char *args[64];
	char *line = ft_strdup(buff);
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
		return (0);
	}
	if (ft_strncmp(args[0], "exit", 5) == 0)
	{
		free(line);
		exit(0);
	}
	if (ft_strncmp(args[0], "cd",3) == 0)
		vash_cd(args);
	else if (ft_strncmp(args[0], "echo",5) == 0)
		vash_echo(args);
	else if (ft_strncmp(args[0], "pwd",4) == 0)
		//vash_pwd(args);
		ft_pwd();
	else if (ft_strncmp(args[0], "env",4) == 0)
		vash_env();
	
	else if (ft_strncmp(args[0], "export",7) == 0)
	{
		if (args[1] == NULL)
			vash_env();
		else
			vash_export(args);
	}
	else if (ft_strncmp(args[0], "unset",6) == 0)
		vash_unset(args);
	// vash_launch(args);
	else
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}
