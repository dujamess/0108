/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 16:32:41 by mmondad           #+#    #+#             */
/*   Updated: 2024-07-15 16:32:41 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_flag(char *str, int *i, int *flag, t_info *info)
{
	int	tmp;

	tmp = info->quotes;
	while (check_escape(str[*i]))
		(*i)++;
	while (str[*i] == '\'' || str[*i] == '\"')
		set_val(str[(*i)++], info);
	if (info->quotes)
	{
		while (info->quotes)
			set_val(str[(*i)++], info);
		*flag = 1;
		return (*i);
	}
	if (str[*i] == '$')
	{
		while (str[*i] == '$')
			(*i)++;
		*flag = 1;
		info->quotes = tmp;
		return (*i);
	}
	info->quotes = tmp;
	return (0);
}

int	heredoc_ex_l(char *str, int *flag, t_info *info)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (str[++i])
	{
		set_val(str[i], info);
		if (str[i] == '$')
			return (0);
		if (!info->quotes && str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			if (init_flag(str, &i, flag, info))
				tmp = i;
			while (alpha_n(str[i]))
				i++;
			if (str[i] == '\"' || str[i] == '\'')
				info->heredoc_f = 1;
			if (flag)
				return (tmp);
			return (0);
		}
	}
	return (i);
}
