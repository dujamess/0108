/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:11:38 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 17:56:18 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	some;
	char			*s3;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2)
		return (0);
	some = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * (some +1));
	if (!s3)
		return (NULL);
	while (s1[i] && i < some)
		s3[j++] = s1[i++];
	while (s2[k] && j < some)
		s3[j++] = s2[k++];
	s3[j] = '\0';
	return (s3);
}

int	ft_strcmp1(char *s1, char *s2)
{
	while (s1 && s2 && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strchr1(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strncpy1(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strdup1(char *s)
{
	char			*str;
	unsigned int	i;

	i = 0;
	i = ft_strlen(s);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
