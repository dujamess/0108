/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:59:30 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 16:42:51 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dans_env(char *av, t_variable *env, int n)
{
	int	i;

	i = 0;
	while (env[i].nom)
	{
		if (ft_strncmp1(av, env[i].nom, n) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	checck_plus(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '+')
		i++;
	return (i);
}

int	calcul_count(char **av, t_variable *env, int count, int i)
{
	int	n;

	while (av && av[i])
	{
		n = 0;
		if (valid_argument(av[i]) == 1)
		{
			n = position_egal(av[i]);
			if (n != 0 && av[i][n - 1] && av[i][n - 1] == '+')
				n = n - 1;
			if ((n != 0) && (check_dans_env(av[i], env, n)))
				count++;
			if (n == 0)
			{
				if (check_dans_env(av[i], env, ft_strlen(av[i])))
					count++;
			}
		}
		i++;
	}
	return (count);
}

void	remplir_encien_env(t_variable *env, t_variable *new_env, int *ptr)
{
	int	i;

	i = *ptr;
	while (env[i].nom)
	{
		free(new_env[i].nom);
		free(new_env[i].valeur);
		free(new_env[i].env_join);
		new_env[i].nom = ft_strdup1(env[i].nom);
		new_env[i].valeur = ft_strdup1(env[i].valeur);
		new_env[i].env_join = ft_strdup1(env[i].env_join);
		new_env[i].flag_print = env[i].flag_print;
		new_env[i].flag_ega = env[i].flag_ega;
		i++;
	}
	*ptr = i;
}

void	remplir_new_env(t_variable *new_env, int *ptr, int *count)
{
	int	i;

	i = *ptr;
	while (*count > 0)
	{
		new_env[i].nom = ft_strdup1("");
		new_env[i].valeur = ft_strdup1("");
		new_env[i].env_join = ft_strdup1("");
		new_env[i].flag_print = 1;
		new_env[i].flag_ega = 0;
		i++;
		(*count)--;
	}
	*ptr = i;
}
