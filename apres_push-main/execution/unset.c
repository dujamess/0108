/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:35:53 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 01:19:49 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_varible(char **av, t_variable *env, t_variable *new_env, int *ptr)
{
	int	i;
	int	j;
	int	s;

	i = 0;
	j = 0;
	s = *ptr;
	while (env[i].nom)
	{
		j = position_var_unset(env, av, &i);
		if (av[j] == NULL)
		{
			new_env[s] = update_env(env[i]);
			s++;
		}
		i++;
	}
	new_env[s].valeur = NULL;
	new_env[s].nom = NULL;
	new_env[s].env_join = NULL;
	new_env[0].env_exec = NULL;
}

t_variable	*builtin_unset(char **av, t_variable *env)
{
	int			i;
	int			size;
	int			s;
	int			*flag;
	t_variable	*new_env;

	i = 0;
	s = 0;
	while (env && env[i].nom)
		i++;
	flag = malloc(sizeof(int) * (i + 1));
	if (!flag)
		return (NULL);
	unistial_vlag(flag, i);
	size = check_size_new_array(av, env, flag);
	free(flag);
	new_env = malloc(sizeof(t_variable) * size);
	if (!new_env)
		return (NULL);
	unset_varible(av, env, new_env, &s);
	free_d(env->env_exec);
	env->env_exec = NULL;
	return (new_env);
}

void	check_error_max_exit(char **av)
{
	if ((ft_isdigit1(av[1]) == 0))
		exit_error(av);
	if (av[1][0] != '-')
	{
		if (ft_strlen(av[1]) - skip_sero(av[1]) > 19)
			exit_error(av);
		if ((ft_strlen(av[1]) - skip_sero(av[1]) > 19)
			&& check_size_max(av[1]) != 0)
			exit_error(av);
	}
	if ((ft_strlen(av[1])) == 19 && check_size_max(av[1]) != 0)
		exit_error(av);
	else if ((ft_strlen(av[1]) - skip_sero(av[1]) >= 20)
		&& (av[1][0] == '-') && check_size_max(av[1]) != 0)
		exit_error(av);
}
