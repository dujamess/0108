/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:51:09 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/28 20:22:13 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	buffer_lenght(char *buffer)
{
	int	i;

	i = 0;
	while (buffer && buffer[i])
	{
		if (!check_escape(buffer[i]))
			return (1);
		i++;
	}
	return (0);
}

int	line_lenght(t_info *info, int flag)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (check_escape(info->env->valeur[len]) && info->quotes)
		len++;
	while (info->env->valeur[len])
	{
		if (!len && !info->i && flag)
			i++;
		else if (len && !check_escape(info->env->valeur[len])
			&& check_escape(info->env->valeur[len - 1]) && !info->i && flag)
			i++;
		else if (len && check_escape(info->env->valeur[len])
			&& !check_escape(info->env->valeur[len - 1]) && !info->i && flag)
			i++;
		i++;
		len++;
	}
	return (i + 1);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_escape(str[i]))
			i++;
		if (str[i] != 0)
			count++;
		while (str[i] && !check_escape(str[i]))
			i++;
	}
	return (count);
}

int	until_del(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

int	dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && !check_escape(str[i]))
		i++;
	return (i);
}
