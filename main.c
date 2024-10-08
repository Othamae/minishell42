/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:23:13 by vconesa-          #+#    #+#             */
/*   Updated: 2024/10/08 14:24:20 by vconesa-         ###   ########.fr       */
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
		printf("Input: %s\n", buff);
	}

}