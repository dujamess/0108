/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-08 10:26:55 by mmondad           #+#    #+#             */
/*   Updated: 2024-06-08 10:26:55 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_len(t_list *lst, t_info *info)
{
	info->reds_l = 0;
	info->parts_l = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type > PIPE)
		{
			info->reds_l += 2;
			lst = lst->next;
		}
		else
			info->parts_l++;
		if (lst)
			lst = lst->next;
	}
}

void	new_fnode(void *data, t_info *info)
{
	t_heapnode	*node;

	node = malloc(sizeof(t_heapnode));
	if (!node)
		free_list(info, 1);
	node->data = data;
	node->next = NULL;
	add_back_h(&(info->head_h), node);
}

void	init_list(t_info *info, t_plist *node)
{
	if (info->reds_l)
	{
		node->reds = malloc (sizeof (char *) * (info->reds_l + 1));
		if (!node->reds)
			free_list(info, 1);
		new_fnode(node->reds, info);
	}
	if (info->reds_l)
	{
		node->types = malloc(sizeof (int) * (info->reds_l));
		if (!node->types)
			free_list(info, 1);
		new_fnode(node->types, info);
	}
}

t_plist	*new_pnode(t_info *info)
{
	t_plist	*node;

	node = malloc(sizeof (t_plist));
	if (!node)
		free_list(info, 1);
	new_fnode(node, info);
	node->parts = NULL;
	node->reds = NULL;
	node->index = 0;
	node->parts = malloc (sizeof (char *) * (info->parts_l + 1));
	if (!node->parts)
		free_list(info, 1);
	new_fnode(node->parts, info);
	init_list(info, node);
	node->next = NULL;
	return (node);
}

void	new_node(char *str, int type, t_info *info)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		free_list(info, 1);
	new_fnode(node, info);
	node->next = NULL;
	node->type = type;
	node->txt = str;
	add_back(&info->list, node);
}
