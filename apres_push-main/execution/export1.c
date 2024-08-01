/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:55:39 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/19 19:00:05 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr1(char const *s, int start, int len)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen((char *) s) - start < len)
		len = ft_strlen((char *) s) - start;
	if (start > ft_strlen((char *) s))
		return (ft_strdup1(""));
	str = malloc (sizeof (char) * (len +1));
	if (!str)
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	position_egal(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	if (av[i] == '\0')
		return (0);
	return (i);
}

int	valid_argument(char *av)
{
	int	i;

	i = 0;
	if (!((av[0] >= 'a' && av[0] <= 'z')
			|| (av[0] >= 'A' && av[0] <= 'Z')
			|| av[0] == '_'))
		return (0);
	while (av[i] && av[i] != '=')
	{
		if (number_plus(av) != 1)
			return (0);
		if (av[i] == '+' && av[i + 1] != '=')
			return (0);
		if (!((av[i] >= 'a' && av[i] <= 'z')
				|| (av[i] >= 'A' && av[i] <= 'Z')
				|| (av[i] >= '0' && av[i] <= '9')
				|| av[i] == '_' || av[i] == '+' || av[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	size_array_env(t_variable *env)
{
	int	i;

	i = 0;
	while (env[i].nom)
		i++;
	return (i);
}

int	ft_strncmp1(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if (s1[i] - s2[i] > 0)
				return (1);
			else
				return (-1);
		}
	}
	if (s2[i] == '\0')
		return (0);
	return (2);
}
