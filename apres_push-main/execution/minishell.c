/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:23:31 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 13:37:10 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_variable	*pwd_env1(t_variable *my_env, t_info *info,
	t_variable *pwd_env, char *str)
{
	if (str)
	{
		if (check_variable(my_env, "_", info->var) != NULL)
		{
			pwd_env = check_variable(my_env, "_", info->var);
			free(pwd_env->valeur);
			pwd_env->valeur = ft_strdup1(str);
			return (pwd_env);
		}
	}
	return (NULL);
}

t_variable	*set_env(t_variable *my_env, char **penv)
{
	if (*penv == NULL)
		my_env = env_reserver(my_env);
	else
		my_env = builtin_env(penv);
	return (my_env);
}
