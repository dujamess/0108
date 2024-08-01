/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:29:13 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/28 20:04:15 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	len_f(char *s1, t_split *data, t_info *info)
{
	(void)info;
	data->len = 0;
	while (s1[data->i] && !check_sep(s1[data->i]))
	{
		if (s1[data->i] == '\'' || s1[data->i] == '\"')
		{
			if (s1[data->i] == '\'')
				data->len += 2;
			data->tmp = s1[data->i++];
			while (s1[data->i] && s1[data->i++] != data->tmp)
				data->len++;
		}
		else
		{
			data->i++;
			data->len++;
		}
	}
}

void	set_val(char c, t_info *info)
{
	if (c == '\'' && !info->quotes)
		info->quotes = '\'';
	else if (c == '\'' && info->quotes == '\'')
		info->quotes = 0;
	else if (c == '\"' && !info->quotes)
		info->quotes = '\"';
	else if (c == '\"' && info->quotes == '\"')
		info->quotes = 0;
}

int	until_d(char *str, t_info *info)
{
	int	i;

	i = 0;
	(void)info;
	if (!str)
		return (0);
	while (str[i] && str[i] != '$')
	{
		set_val(str[i], info);
		i++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
