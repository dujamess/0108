/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_varible.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:55:44 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 23:26:37 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_builtin_redirection(t_info	*info, t_variable *my_env, int *ptr)
{
	int		count;

	count = *ptr;
	run_buil_red(my_env, info, &count);
}

int	number_commande(t_info info)
{
	int	count;

	count = 0;
	if (info.plist && info.plist->parts)
	{
		while (info.plist->parts[count])
			count++;
	}
	return (count);
}

t_variable	*env_reserver(t_variable *env_nu)
{
	char	*str;

	env_nu = malloc(sizeof(t_variable) * 4);
	env_nu[0].nom = ft_strdup1("PWD");
	env_nu[0].valeur = getcwd(NULL, 0);
	env_nu[0].flag_print = 0;
	str = ft_strjoin1(env_nu[0].nom, "=");
	env_nu[0].env_join = ft_strjoin1(str, env_nu[0].valeur);
	free(str);
	env_nu[1].nom = ft_strdup1("SHLVL");
	env_nu[1].valeur = ft_strdup1("0");
	env_nu[1].flag_print = 0;
	str = ft_strjoin1(env_nu[1].nom, "=");
	env_nu[1].env_join = ft_strjoin1(str, env_nu[1].valeur);
	free(str);
	env_nu[2].nom = ft_strdup1("_");
	env_nu[2].valeur = ft_strdup1("/usr/bin/env");
	env_nu[2].flag_print = 0;
	str = ft_strjoin1(env_nu[2].nom, "=");
	env_nu[2].env_join = ft_strjoin1(str, env_nu[2].valeur);
	free(str);
	env_nu[3].nom = NULL;
	env_nu[3].valeur = NULL;
	env_nu[3].env_join = NULL;
	return (env_nu);
}
