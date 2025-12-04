/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:50:47 by noctis            #+#    #+#             */
/*   Updated: 2025/12/03 18:07:29 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_levels	*ft_creat_new_list(char *path)
{
	t_levels	*n;

	n = malloc(sizeof(t_levels));
	if (!n)
		return (NULL);
	n->path = ft_strdup(path);
	if (!n->path)
		return (free(n), NULL);
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

void	ft_add_list_end(t_levels **lvls, t_levels *n)
{
	t_levels	*ptr;

	if (!lvls)
		return ;
	if (!*lvls)
	{
		*lvls = n;
		return ;
	}
	ptr = (*lvls);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = n;
	n->prev = ptr;
	return ;
}

int	ft_list_count(t_levels *lvls)
{
	int			i;
	t_levels	*ptr;

	i = 0;
	ptr = lvls;
	while (ptr->next)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
