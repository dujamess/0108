/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:22:39 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/28 09:47:25 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fonction_swap(int *ptr, int *ptr1, t_variable *my_env)
{
	char	*tmp_n;
	char	*tmp_v;
	int		tmp_flag;
	int		i;
	int		j;

	i = *ptr;
	j = *ptr1;
	tmp_n = ft_strdup1(my_env[i].nom);
	tmp_v = ft_strdup1(my_env[i].valeur);
	tmp_flag = my_env[i].flag_print;
	free(my_env[i].nom);
	free(my_env[i].valeur);
	my_env[i].nom = ft_strdup1(my_env[j].nom);
	my_env[i].valeur = ft_strdup1(my_env[j].valeur);
	my_env[i].flag_print = my_env[j].flag_print;
	free(my_env[j].nom);
	free(my_env[j].valeur);
	my_env[j].nom = ft_strdup1(tmp_n);
	my_env[j].valeur = ft_strdup1(tmp_v);
	my_env[j].flag_print = tmp_flag;
	free(tmp_n);
	free(tmp_v);
}

void	fonct_sort_env( t_variable *my_env)
{
	int	i;
	int	j;

	i = 0;
	while (my_env[i].nom)
	{
		j = i + 1;
		while (my_env[j].nom)
		{
			if (ft_strcmp1(my_env[i].nom, my_env[j].nom) > 0)
				fonction_swap(&i, &j, my_env);
			j++;
		}
		i++;
	}
}

void	sort_env(t_variable *my_env)
{
	fonct_sort_env(my_env);
}
