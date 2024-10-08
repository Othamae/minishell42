/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/08 14:38:20 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getcmd(char *buff, int nbuf)
{
	char	*input;

	ft_memset(buff, 0, nbuf);
	input = readline(PROMP);
	if (!input)
		return -1;
	ft_strlcpy(buff, input, nbuf);	
	if(buff[0] == 0) // EOF
		return -1;
	free(input);
	return 0;
}


int main(void)
{
	static char	buff[100];
	int			fd;

	while((fd = open("/dev/tty", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}
	
	while((getcmd(buff,sizeof(buff)) >= 0))
	{
		if (buff[0] == 'c' && buff[1] == 'd' && buff[2] == ' ')
		{
		printf("Input: %c\n", buff[0]);
		printf("Input: %c\n", buff[1]);
		printf("Input: %s\n", buff+3);

			buff[ft_strlen(buff -1)] = 0;
			if (chdir(buff+3) < 0)
				printf("cannot cd %s\n", buff+3);
			continue;
		}
		printf("Input: %s\n", buff);
	}

}