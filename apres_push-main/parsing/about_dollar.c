/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:24:15 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/28 17:28:27 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_dollar(t_info *info)
{
	if (info->line[info->count] == '$' && info->line[info->count + 1] == '$')
	{
		info->count += 2;
		return ("$$");
	}
	return (NULL);
}

int	dollar(char c, t_info *info)
{
	if (c == '$' && !info->flag)
		return (1);
	else if (c != '$')
		info->flag = 1;
	else if (c == '$' && info->flag)
	{
		info->flag = 0;
		return (0);
	}
	return (1);
}

char	*fake_var(t_info *info, int i)
{
	char	*dlr;

	info->flag = 0;
	dlr = append_dollar(info);
	if (dlr)
		return (dlr);
	if ((info->line[i] == '\'' || info->line[i] == '\"') && !info->quotes)
	{
		info->count++;
		return (NULL);
	}
	return (after_d(info));
}
