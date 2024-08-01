/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:06:13 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 19:08:37 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	variable_sans_egal(char *av, t_variable *new_env, int *ptr)
{
	int	i;

	i = *ptr;
	free(new_env[i].nom);
	free(new_env[i].valeur);
	free(new_env[i].env_join);
	new_env[i].nom = ft_strdup1(av);
	new_env[i].valeur = ft_strdup1("");
	new_env[i].env_join = ft_strdup1(av);
	new_env[i].flag_print = 1;
	new_env[i].flag_ega = 0;
	i++;
	*ptr = i;
}

void	variable_new_env(t_variable *new_env, char *av, int *ptr, int *ptr1)
{
	int	n;
	int	i;

	i = *ptr1;
	n = *ptr;
	n = position_egal(av);
	if (n != 0 && av[n - 1] && av[n - 1] == '+')
		n = n - 1;
	free(new_env[i].nom);
	new_env[i].nom = ft_substr1(av, 0, n);
	n = position_egal(av);
	if (n == 0)
		new_env[i].flag_ega = 0;
	else
		new_env[i].flag_ega = 1;
	free(new_env[i].valeur);
	free(new_env[i].env_join);
	new_env[i].valeur = ft_strdup1(av + n + 1);
	new_env[i].env_join = ft_strdup1(av);
	new_env[i].flag_print = 0;
	i++;
	*ptr1 = i;
}

void	edit_varible(t_variable *new_env, char *av, int *ptr, int *flags)
{
	int		k;
	int		n;
	int		flag;
	char	*ptr1;

	flag = *flags;
	n = *ptr;
	k = -1;
	while (new_env[++k].nom)
	{
		edit_varible2(new_env, k, n);
		if ((flag == 1) && (ft_strncmp1(av, new_env[k].nom, n - 2) == 0))
		{
			ptr1 = new_env[k].valeur;
			new_env[k].valeur = ft_strjoin1(new_env[k].valeur, av + n);
			free(ptr1);
			ptr1 = new_env[k].env_join;
			new_env[k].env_join = ft_strjoin1(new_env[k].env_join, av + n);
			free(ptr1);
			new_env[k].flag_print = 0;
			flag = 0;
			break ;
		}
		else_export(new_env, av, &n, &k);
	}
}

void	variable_deja_env(t_variable *new_env, char *av)
{
	int	flag;
	int	n;

	flag = 0;
	n = position_egal(av);
	if (n != 0 && av[n - 1] && av[n - 1] == '+')
	{
		n = n + 1;
		flag = 1;
	}
	edit_varible(new_env, av, &n, &flag);
}

void	export_variable(char *av, t_variable *new_env, int n, int *ptr)
{
	if (valid_argument(av) == 1)
	{
		n = position_egal(av);
		if (n != 0 && av[n - 1] && av[n - 1] == '+')
			n = n - 1;
		if (n == 0)
		{
			if (check_dans_env(av, new_env, ft_strlen(av)))
				variable_sans_egal(av, new_env, ptr);
		}
		else if (n != 0 && check_dans_env(av, new_env, n))
			variable_new_env(new_env, av, &n, ptr);
		else
			variable_deja_env(new_env, av);
	}
	else
	{
		write(2, av, ft_strlen(av));
		ft_putstr(" : not a valid identifier\n", 2);
		g_general->exit_status = 1;
	}
}
