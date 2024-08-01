/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:49:35 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/28 09:46:58 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unistial_vlag(int *flag, int size)
{
	int	s;

	s = 0;
	while (s <= size)
	{
		flag[s] = 0;
		s++;
	}
}

int	check_size_new_array(char **av, t_variable *env, int *flag)
{
	int	count;
	int	i;
	int	j;

	j = 0;
	i = 0;
	count = 0;
	while (av[i])
	{
		j = 0;
		while (env[j].nom)
		{
			if ((ft_strcmp1(av[i], env[j].nom) == 0)
				&& flag[j] == 0 && (ft_strcmp1(av[i], "_") != 0))
			{
				flag[j] = 1;
				count++;
			}
			j++;
		}
		i++;
	}
	return ((j - count) + 1);
}

void	free_env(t_variable *env)
{
	int	i;

	if (env == NULL)
		return ;
	i = 0;
	while (env[i].nom != NULL)
	{
		free(env[i].nom);
		free(env[i].valeur);
		i++;
	}
	free(env);
}

t_variable	update_env(t_variable env_line)
{
	t_variable	var;
	char		*str;

	var.nom = ft_strdup1(env_line.nom);
	var.valeur = ft_strdup1(env_line.valeur);
	str = ft_strjoin1(var.nom, "=");
	var.env_join = ft_strjoin1(str, var.valeur);
	free(str);
	var.flag_print = env_line.flag_print;
	return (var);
}

int	position_var_unset(t_variable *env, char **av, int *ptr)
{
	int	i;
	int	j;

	i = *ptr;
	j = 0;
	while (av[j])
	{
		if (ft_strcmp1(av[j], env[i].nom) != 0 || ft_strcmp1(av[j], "_") == 0)
			j++;
		else
			break ;
	}
	return (j);
}
