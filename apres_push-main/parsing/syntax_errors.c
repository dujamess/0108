/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:14:24 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/28 19:15:06 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unknown_type(t_list list, t_info info)
{
	if (info.quotes_tmp)
	{
		stx_message(NULL, info.quotes_tmp);
		return (1);
	}
	if (list.type == UNKNOWN)
	{
		if (list.txt[0] == '|')
			stx_message(NULL, '|');
		else if (ft_strlen(list.txt) > 3)
			stx_message(list.txt + ft_strlen(list.txt) - 2, 0);
		else
			stx_message(NULL, list.txt[0]);
		return (1);
	}
	return (0);
}

int	known_type(t_list list)
{
	if ((list.next && list.type == PIPE
			&& list.next->type == PIPE))
		return (stx_message(NULL, '|'), 1);
	if ((list.next && list.type > PIPE
			&& list.next->type != WORD))
	{
		if (!list.next->type)
			stx_message(list.next->txt + ft_strlen(list.next->txt) - 2, 0);
		else
			stx_message(list.next->txt, 0);
		return (1);
	}
	if ((!list.next && list.type != WORD))
	{
		if (list.type == PIPE)
			stx_message(NULL, '|');
		else
			stx_message("newline", 0);
		return (1);
	}
	return (0);
}

int	stx_errors(t_info info)
{
	t_list	*list;

	list = info.list;
	if (list && list->type == PIPE)
		return (stx_message(NULL, '|'), 1);
	while (list)
	{
		if (unknown_type(*list, info))
			return (1);
		if (known_type(*list))
			return (1);
		list = list->next;
	}
	return (0);
}
