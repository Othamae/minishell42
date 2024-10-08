/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:27:41 by vconesa-          #+#    #+#             */
/*   Updated: 2024/05/27 21:07:42 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst->content);
		free(lst);
	}
}
// Description: Takes as a parameter a node and frees the memory 
// of the node’s content using the function ’del’ given 
// as a parameter and free the node. 
// The memory of ’next’ must not be freed.