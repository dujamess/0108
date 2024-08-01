/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:44:49 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/28 19:13:57 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	edit_varible2(t_variable *new_env, int k, int n)
{
	if (n == 0)
		new_env[k].flag_ega = 0;
	else
		new_env[k].flag_ega = 1;
}

void	else_export(t_variable *new_env, char *av, int *n, int *k)
{
	if (ft_strncmp1(av, new_env[*k].nom, *n) == 0)
		edit_varible1(new_env, n, av, k);
}

void	edit_varible1(t_variable *new_env, int *ptrn, char *av, int *ptrk)
{
	int		n;
	int		k;
	char	*ptr1;

	n = *ptrn;
	k = *ptrk;
	ptr1 = new_env[k].valeur;
	new_env[k].valeur = ft_strdup1(av + n + 1);
	free(ptr1);
	ptr1 = new_env[k].env_join;
	new_env[k].env_join = ft_strdup1(av);
	free(ptr1);
	new_env[k].flag_print = 0;
}

int	number_plus(char *av)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (av[i] && av[i] != '=')
	{
		if (av[i] == '+')
			count++;
		i++;
	}
	if (count <= 1)
		return (1);
	return (0);
}

t_variable	*builtin_export(char **av, t_variable *env)
{
	int			count;
	int			i;
	int			n;
	int			j;
	t_variable	*new_env;

	count = 0;
	i = 1;
	n = 0;
	count = calcul_count(av, env, count, i);
	new_env = ft_calloc(sizeof(t_variable), (size_array_env(env) + count + 1));
	i = 0;
	remplir_encien_env(env, new_env, &i);
	remplir_new_env (new_env, &i, &count);
	i = size_array_env(env);
	j = 1;
	while (av && av[j])
	{
		export_variable(av[j], new_env, n, &i);
		j++;
	}
	free_d(env->env_exec);
	env->env_exec = NULL;
	return (new_env);
}
