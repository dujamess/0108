/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:08:30 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/27 15:03:58 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_file(t_file **list, t_file *new_node)
{
	t_file	*tmp;

	tmp = *list;
	if (list && *list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	new_node_file(void *data, t_info *info, t_file **head)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		free_list(info, 1);
	new_fnode(node, info);
	node->file_name = data;
	node->next = NULL;
	add_back_file(head, node);
}
