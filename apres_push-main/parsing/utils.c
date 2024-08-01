/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:37:59 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/29 10:19:06 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ss2;
	unsigned char	*ss1;

	ss1 = (unsigned char *) s1;
	ss2 = (unsigned char *) s2;
	i = 0;
	while ((ss1[i] || ss2[i]))
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(t_info *info, t_split data)
{
	char	*cpy;

	data.j = 0;
	info->quotes = 0;
	len_f(info->line, &data, info);
	cpy = allocate(info, data.len + 1);
	if (!cpy)
		free_list(info, 1);
	while (info->line[info->i] && !check_sep(info->line[info->i]))
	{
		if (info->line[info->i] == '\"' || info->line[info->i] == '\'')
		{
			data.tmp = info->line[info->i];
			if (info->line[info->i++] == '\'' && info->token_type)
				cpy[data.j++] = '\'';
			while (info->line[info->i] && info->line[info->i++] != data.tmp)
				cpy[data.j++] = info->line[info->i - 1];
			if (data.tmp == '\'' && info->token_type)
				cpy[data.j++] = '\'';
		}
		else
			cpy[data.j++] = info->line[info->i++];
	}
	cpy[data.j] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2, t_info *info)
{
	int		i;
	int		j;
	char	*str;

	str = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		free_list(info, 1);
	new_fnode(str, info);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = ((char *)s2)[j];
		j++;
	}
	str[i + j] = 0;
	return (str);
}
