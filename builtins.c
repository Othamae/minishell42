/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/10 17:13:59 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		return (0);
	}
	if (strcmp(args[0], "cd") == 0)
		vash_cd(args);
	else if (strcmp(args[0], "echo") == 0)
		vash_echo(args);
	else if (strcmp(args[0], "pwd") == 0)
		//vash_pwd(args);
		ft_pwd();
	else if (strcmp(args[0], "env") == 0)
		vash_env(args);
	else
	{
		free(line);
		return (0);
	}
	// vash_launch(args);
	free(line);
	return (1);
}
