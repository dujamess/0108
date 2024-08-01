/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondad <mmondad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:32:01 by mmondad           #+#    #+#             */
/*   Updated: 2023/11/21 18:49:11 by mmondad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len, t_info *info)
{
	char	*str;
	int		j;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	j = 0;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	new_fnode(str, info);
	while (j < len)
	{
		if (s[start + j] == '|')
			info->pipe = 1;
		str[j] = s[start + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
