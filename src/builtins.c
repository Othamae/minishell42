/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:32 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 12:19:18 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"



// int	vash_launch(char **argv)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execvp(argv[0], argv) == -1)
// 		{
// 			perror("type in a valid command");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid > 0)
// 		{
// 			wait(NULL);
// 		}

// 	else {
// 		perror("a forking error occured");
// 		exit(EXIT_FAILURE);
// 	}
// 	return 0;
// }

// int vash_cd(char **args)
// {
// 	char *path;
// 	char cwd[1024];

// 	if (args[1] == NULL)
// 	{
// 		path = getenv("HOME");
// 		if (path == NULL)
// 		{
// 			perror("error: cd");
// 			return -1;
// 		}
// 	}
// 	else
// 		path = args[1];
// 	if (chdir(path) != 0)
// 	{
// 		perror("error: cd");
// 		return -1;
// 	}
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		;
// 	else
// 		perror("Minishell: cd: no such file or directory");
// 	return 0;
// }

// int vash_echo(char **args, t_context *context)
// {
// 	char old_str[1024];
// 	int i = 1;
// 	int j = 0;
// 	int no_newline = 0;
// 	char *new_str;

// 	if (args[1] == NULL)
// 	{
// 		printf("\n");
// 		return 0;
// 	}
// 	if (strncmp(args[1], "-n", 3) == 0)
// 	{
// 		no_newline = 1;
// 		i++;
// 	}

// 	if (ft_strncmp(args[1], "$?", 3) == 0)
// 	{
// 		ft_printf("%d\n", context->last_status);
// 		exit(0);
// 	}

// 	while (args[i] != NULL)
// 	{

// 		int k = 0;
// 		if ((args[i][0] == '$') || (args[i][1] == '$'
// 			&& (args[i][0] == 34 && (args[i][ft_strlen (args[i]) - 1] == 34)))
// 			|| (args[i][2] == '$' && (args[i][0] == 34 && (args[i][ft_strlen (args[i]) - 1] == 34))))
// 		{
// 			if (args[i][0] == '$')
// 			{
// 				char *env_var_name = args[i] + 1;
// 				char *env_var_value = getenv(env_var_name);
// 				if (env_var_value)
// 				{
// 					int l = 0;
// 					while (env_var_value[l] != '\0')
// 						old_str[j++] = env_var_value[l++];
// 				}
// 				else
// 				{
// 					while (args[i][k] != '\0')
// 						old_str[j++] = args[i][k++];
// 				}
// 			}
// 			else if (args[i][1] == '$'
// 			&& (args[i][0] == 34 && (args[i][ft_strlen (args[i]) - 1] == 34)))
// 			{
// 				char *env_var_name = args[i] + 2;
// 				env_var_name[strlen(env_var_name) - 1] = '\0';

// 				char *env_var_value = getenv(env_var_name);
// 				if (env_var_value)
// 				{
// 					int l = 0;
// 					while (env_var_value[l] != '\0')
// 						old_str[j++] = env_var_value[l++];
// 				}
// 				else
// 				{
// 					old_str[j++] = '"';
// 					while (args[i][k] != '\0')
// 						old_str[j++] = args[i][k++];
// 					old_str[j++] = '"';
// 				}
// 			}
// 			else
// 			{
// 				char *env_var_name = args[i] + 3;
// 				env_var_name[strlen(env_var_name) - 2] = '\0';

// 				char *env_var_value = getenv(env_var_name);
// 				if (env_var_value)
// 				{
// 					int l = 0;
// 					while (env_var_value[l] != '\0')
// 					{
// 						old_str[j++] = env_var_value[l++];
// 						old_str[j] = '\0';
// 						write (1, "'", 1);
// 						write (1, old_str, ft_strlen(old_str));
// 						write (1, "'\n", 2);
// 						return (0);

// 					}
// 				}
// 				else
// 				{
// 					old_str[j++] = '"';
// 					while (args[i][k] != '\0')
// 						old_str[j++] = args[i][k++];
// 					old_str[j] = '"';
// 				}
// 			}
// 		}
// 		else
// 		{
// 			while (args[i][k] != '\0')
// 				old_str[j++] = args[i][k++];
// 		}
// 		if (args[i + 1] != NULL)
// 			old_str[j++] = ' ';
// 		i++;
// 	}
// 	old_str[j] = '\0';
// 	j = 0;
// 	i = 1;
// 	if (old_str[j] == '\0')
// 	{
// 		if (no_newline)
// 			;
// 		else
// 			printf("\n");
// 		return (0);
// 	}
// 	new_str = (char *)malloc(strlen(old_str) + 1);
// 	if (new_str == NULL)
// 	{
// 		printf("error allocating new string");
// 		return (0);
// 	}
// 	if ((old_str[0] == 34 && old_str[strlen(old_str) - 1] == 34) ||
// 		(old_str[0] == 39 && old_str[strlen(old_str) - 1] == 39))
// 	{
// 		while (old_str[i] != old_str[strlen(old_str) - 1])
// 			new_str[j++] = old_str[i++];
// 		new_str[j] = '\0';
// 	}
// 	else
// 		strcpy(new_str, old_str);

// 	if (no_newline)
// 		printf("%s", new_str);
// 	else
// 		printf("%s\n", new_str);

// 	if (new_str != old_str)
// 		free(new_str);

// 	return (0);
// }


// int		ft_pwd(void)
// {
// 	char	cwd[4096]; //4096

// 	if (getcwd(cwd, 4096))
// 	{
// 		printf("%s\n", cwd);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// int vash_pwd(void)
// {
// 	char *pwd = getenv("PWD");
// 	if (pwd != NULL)
// 	{
// 		printf("%s\n", pwd);
// 	}
// 	return 0;
// }

// int vash_export(char **args)
// {
// 	extern char **environ;
// 	int i = 0;
// 	char *new_exp;
// 	char *equal_sign;
// 	char *value_part;
// 	int len = ft_strlen(args[1]);

// 	if (ft_strstr(args[1], "==") != NULL)
// 	{
// 		printf("Error: invalid format, '==' found\n");
// 		return 1;
// 	}
// 	if (count_char(args[1], '\'') > 2 || count_char(args[1], '"') > 2)
// 	{
// 		printf("Error: invalid format, quotes appear too many times\n");
// 		return 1;
// 	}
// 	equal_sign = strchr(args[1], '=');

// 	if (equal_sign == NULL)
// 	{
// 		new_exp = malloc(len + 1);
// 		if (!new_exp)
// 		{
// 			perror("Error: memory allocation failed");
// 			return 1;
// 		}
// 		strcpy(new_exp, args[1]);

// 		while (environ[i] != NULL)
// 		{
// 			if (ft_strncmp(environ[i], new_exp, len) == 0 && environ[i][len] == '\0')
// 			{
// 				return 0;
// 			}
// 			i++;
// 		}

// 		environ[i] = new_exp;
// 		environ[i + 1] = NULL;

// 		return 0;
// 	}
// 	new_exp = malloc(len + 1);
// 	if (!new_exp)
// 	{
// 		perror("Error: memory allocation failed");
// 		return 1;
// 	}
// 	value_part = equal_sign + 1;
// 	if ((*value_part == '\'' && value_part[ft_strlen(value_part) - 1] == '\'') ||
// 		(*value_part == '"' && value_part[ft_strlen(value_part) - 1] == '"'))
// 	{
// 		value_part[ft_strlen(value_part) - 1] = '\0';
// 		value_part++;
// 	}
// 	strncpy(new_exp, args[1], equal_sign - args[1] + 1);
// 	strcpy(new_exp + (equal_sign - args[1] + 1), value_part);
// 	while (environ[i] != NULL)
// 	{
// 		if (strncmp(environ[i], new_exp, equal_sign - args[1]) == 0)
// 		{
// 			environ[i] = new_exp;
// 			return 0;
// 		}
// 		i++;
// 	}
// 	environ[i] = new_exp;
// 	environ[i + 1] = NULL;
// 	return 0;
// }


// int vash_env(void)
// {
// 	extern char **environ;
// 	char **env;

// 	env = environ;

// 	while (*env)
// 	{
// 		printf("%s\n", *env);
// 		env++;
// 	}
// 	return 0;
// }

// int vash_unset(char **args)
// {
// 	extern char **environ;
// 	int i, j, k;
// 	int len;

// 	if (args[1] == NULL)
// 	{
// 		printf("Error: expected argument to unset\n");
// 		return 1;
// 	}
// 	k = 1;
// 	while (args[k] != NULL)
// 	{
// 		i = 0;
// 		len = ft_strlen(args[k]);
// 		while (environ[i] != NULL)
// 		{
// 			if (ft_strncmp(environ[i], args[k], len) == 0 && environ[i][len] == '=')
// 			{
// 				j = i;
// 				while (environ[j] != NULL)
// 				{
// 					environ[j] = environ[j + 1];
// 					j++;
// 				}
// 				break;
// 			}
// 			i++;
// 		}
// 		k++;
// 	}
// 	return 0;
// }

// int do_builtins(char *buff)
// {
// 	int i;
// 	char *token;
// 	char *args[64];
// 	char *line = ft_strdup(buff);
// 	i = 0;
// 	token = ft_strtok(line, " ");
// 	while (token != NULL)
// 	{
// 		args[i++] = token;
// 		token = ft_strtok(NULL, " ");
// 	}
// 	args[i] = NULL;
// 	if (args[0] == NULL)
// 	{
// 		free(line);
// 		return (0);
// 	}

// 	if (ft_strncmp(args[0], "exit", 5) == 0)
// 	{
// 		free(line);
// 		exit(0);
// 	}
// 	if (ft_strncmp(args[0], "cd",3) == 0)
// 	 	vash_cd(args);
// 	// else if (ft_strncmp(args[0], "echo",5) == 0)
// 	// 	vash_echo(args);
// 	else if (ft_strncmp(args[0], "pwd",4) == 0)
// 		//vash_pwd(args);
// 		ft_pwd();
// 	else if (ft_strncmp(args[0], "env",4) == 0)
// 		vash_env();

// 	else if ((ft_strncmp(args[0], "export",7) == 0) || ft_strncmp(args[0], "setenv",7) == 0)
// 	{
// 		if (args[1] == NULL && (ft_strncmp(args[0], "setenv",7) != 0))
// 			vash_env();
// 		else
// 			vash_export(args);
// 	}
// 	else if ((ft_strncmp(args[0], "unset",6) == 0) || (ft_strncmp(args[0], "unsetenv", 9) == 0))
// 		vash_unset(args);
// 	// vash_launch(args);
// 	else
// 	{
// 		free(line);
// 		return (0);
// 	}
// 	free(line);
// 	return (1);
// }

// int handle_builtins(char **args, t_context *context)
// {
// 	if (args[0] == NULL)
// 		return 0;
// 	if (ft_strncmp(args[0], "exit", 5) == 0)
// 		exit(0);
// 	else if (ft_strncmp(args[0], "cd", 3) == 0)
// 		vash_cd(args);
// 	else if (ft_strncmp(args[0], "echo", 5) == 0)
// 		vash_echo(args, context);
// 	else if (ft_strncmp(args[0], "pwd", 4) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(args[0], "env", 4) == 0)
// 		vash_env();
// 	else if (ft_strncmp(args[0], "export", 7) == 0 || ft_strncmp(args[0], "setenv", 7) == 0)
// 	{
// 		if (args[1] == NULL && ft_strncmp(args[0], "setenv", 7) != 0)
// 			vash_env();
// 		else
// 			vash_export(args);
// 	}
// 	else if (ft_strncmp(args[0], "unset", 6) == 0 || ft_strncmp(args[0], "unsetenv", 9) == 0)
// 		vash_unset(args);
// 	else
// 		return (0);
// 	context->last_status = 1;
// 	return (1);
// }
