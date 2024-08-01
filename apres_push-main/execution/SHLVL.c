/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SHLVL.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:55:38 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 00:44:02 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_calcul(long int n)
{
	int	i;

	i = 1;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa1(int n, t_info *info)
{
	char		*str;
	int			j;
	long int	m;

	m = (long int)n;
	j = ft_calcul(m);
	str = allocate(info, sizeof(char) * (j) + 1);
	if (!str)
		return (NULL);
	str[j] = '\0';
	j--;
	if (m == 0)
		str[0] = '0';
	if (m < 0)
	{
		str[0] = '-';
		m = m * -1;
	}
	while (m > 0 && j >= 0)
	{
		str[j--] = m % 10 + '0';
		m = m / 10;
	}
	return (str);
}

void	augment_level_shlvl(t_variable *env, t_info *info)
{
	int		i;
	char	*ptr;
	char	*ptr1;
	char	*tmp;

	i = 0;
	while (env[i].nom)
	{
		if (ft_strcmp1(env[i].nom, "SHLVL") == 0)
		{
			ptr = env[i].valeur;
			ptr1 = env[i].env_join;
			tmp = ft_strjoin1(env[i].nom, "=");
			env[i].valeur = ft_strdup1(ft_itoa1(ft_atoi1(env[i].valeur)
						+ 1, info));
			env[i].env_join = ft_strjoin1(tmp, env[i].valeur);
			free(tmp);
			free(ptr);
			free(ptr1);
			break ;
		}
		i++;
	}
}

int	skip_sero(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	return (i);
}

int	check_size_max(char *str)
{
	char	*max;
	char	*min;
	int		len;
	int		i;

	i = 0;
	min = "-9223372036854775808";
	max = "9223372036854775807";
	len = ft_strlen(str) - skip_sero(str);
	if (len == 0)
		return (0);
	if (str[0] != '-' && ft_strcmp1(str, max) > 0)
		return (-1);
	if (str[0] == '-')
	{
		if (ft_strcmp1(str + 1, min + 1) > 0)
			return (-2);
	}
	return (0);
}
