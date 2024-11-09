/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:59:02 by vconesa-          #+#    #+#             */
/*   Updated: 2024/11/09 20:05:11 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2
		&& *s1)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

void	init_qsort(t_qsort *params, void *base, size_t nitems, size_t size)
{
	params->array = (char *)base;
	params->left = params->array;
	params->right = params->array + (nitems - 1) * size;
	params->pivot = params->array + (nitems / 2) * size;
}

int	compare_strings(const void *a, const void *b)
{
	return (ft_strcmp(*(const char **)a, *(const char **)b));
}

static void	swap_elements(char *left, char *right, size_t size)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < size)
	{
		temp = *(left + i);
		*(left + i) = *(right + i);
		*(right + i) = temp;
		i++;
	}
}

void	ft_qsort(void *base, size_t nitems, size_t size,
	int (*compar)(const void *, const void *))
{
	t_qsort	params;

	init_qsort(&params, base, nitems, size);
	if (nitems < 2)
		return ;
	while (params.left <= params.right)
	{
		while (compar(params.left, params.pivot) < 0)
			params.left += size;
		while (compar(params.right, params.pivot) > 0)
			params.right -= size;
		if (params.left <= params.right)
		{
			swap_elements(params.left, params.right, size);
			params.left += size;
			params.right -= size;
		}
	}
	if (params.right > params.array)
		ft_qsort(params.array, (params.right - params.array)
			/ size + 1, size, compar);
	if (params.left < params.array + (nitems - 1) * size)
		ft_qsort(params.left, (params.array + (nitems - 1) * size - params.left)
			/ size + 1, size, compar);
}
