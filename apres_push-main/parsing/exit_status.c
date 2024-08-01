/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:27:35 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/28 17:44:52 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_len(char *str, t_info *info)
{
	int	i;
	int	len;
	int	quotes;

	i = -1;
	len = 0;
	quotes = info->quotes;
	while (str && str[++i])
	{
		set_val(str[i], info);
		if (str[i] == '$' && str[i + 1] == '?' && info->quotes != '\'')
		{
			i++;
			len += ft_strlen(ft_itoa(g_general->exit_status, info));
		}
		else
			len++;
	}
	info->quotes = quotes;
	return (len);
}

void	search_and_replace1(char *line, t_info *info, int *ptr, int *ptr1)
{
	int		j;
	char	*exit;

	j = 0;
	exit = ft_itoa(g_general->exit_status, info);
	(*ptr)++;
	while (exit[j])
		line[(*ptr1)++] = exit[j++];
}

void	search_and_replace(char *str, char *line, t_info *info)
{
	int		len;
	int		i;
	int		quotes;

	quotes = info->quotes;
	i = -1;
	len = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && info->quotes != '\'')
			search_and_replace1(line, info, &i, &len);
		else
		{
			set_val(str[i], info);
			if (str[i] == '$' && str[i + 1] == '$')
				line[len++] = str[i++];
			line[len++] = str[i];
		}
	}
	line[len] = '\0';
	info->quotes = quotes;
}

char	*exit_status(char *str, t_info *info)
{
	int		len;
	char	*line;

	len = exit_len(str, info);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		free_list(info, 0);
	new_fnode(line, info);
	search_and_replace(str, line, info);
	return (line);
}
