/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:39:20 by mmondad           #+#    #+#             */
/*   Updated: 2024/06/03 15:33:29 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_back_h(t_heapnode **list, t_heapnode *new_node)
{
	t_heapnode	*tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	add_back(t_list **list, t_list *new_node)
{
	t_list	*tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	add_back_p(t_plist **list, t_plist *new_node)
{
	t_plist	*tmp;

	tmp = *list;
	if (*list)
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = new_node;
		*list = tmp;
	}
	else
		(*list) = new_node;
}

void	copy_to_list(t_info *info, t_plist *node)
{
	while (info->list && info->list->type != PIPE)
	{
		if (info->list->type > PIPE)
		{
			node->reds[info->i] = info->list->txt;
			node->types[info->i++] = info->list->type;
			if (info->list->next)
			{
				node->reds[info->i] = info->list->next->txt;
				node->types[info->i++] = info->list->next->type;
			}
			info->list = info->list->next;
		}
		else
			node->parts[info->j++] = info->list->txt;
		if (info->list)
			info->list = info->list->next;
	}
}

void	create_plist(t_info *info)
{
	t_list	*lst;
	t_plist	*node;

	lst = info->list;
	while (info->list)
	{
		info->i = 0;
		info->j = 0;
		p_len(info->list, info);
		node = new_pnode(info);
		copy_to_list(info, node);
		if (node->parts)
			node->parts[info->j] = NULL;
		if (node->reds)
			node->reds[info->i] = NULL;
		add_back_p(&info->plist, node);
		if (info->list)
			info->list = info->list->next;
		node->index = ++info->lst_size;
	}
	info->list = lst;
}
