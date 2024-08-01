/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_reserv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:37:20 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 21:22:56 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**return_env(t_variable *my_env)
{
	int		i;
	int		j;
	char	**env_exec;

	i = 0;
	while (my_env && my_env[i].nom)
		i++;
	env_exec = malloc(sizeof(char *) * (i + 1));
	if (!env_exec)
		return (NULL);
	i = 0;
	j = 0;
	while (my_env[i].env_join)
	{
		if (ft_strchr1(my_env[i].env_join, '=') != NULL)
		{
			env_exec[j] = ft_strdup1(my_env[i].env_join);
			j++;
		}
		i++;
	}
	env_exec[j] = NULL;
	return (env_exec);
}

void	remplir_oldpwd(t_variable *my_env, t_pwd *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (my_env[i].nom)
	{
		if ((ft_strcmp1(my_env[i].nom, "OLDPWD") == 0))
		{
			tmp = ft_strjoin1(my_env[i].nom, "=");
			var->oldpwd = ft_strjoin1(tmp,
					my_env[i].valeur);
			free(tmp);
		}
		i++;
	}
}

void	remplir_shlvl(t_variable *my_env, t_pwd *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (my_env[i].nom)
	{
		if ((ft_strcmp1(my_env[i].nom, "SHLVL") == 0))
		{
			tmp = ft_strjoin1(my_env[i].nom, "=");
			var->shlvl = ft_strjoin1(tmp, my_env[i].valeur);
			free(tmp);
		}
		i++;
	}
}

void	open_herdoc_in_main(t_info	info, t_file **head)
{
	t_info	tmp;
	int		r;

	tmp = info;
	while (tmp.plist)
	{
		r = 0;
		while (tmp.plist->reds && tmp.plist->reds[r])
		{
			if (g_general->exit_status)
				break ;
			if (tmp.plist->types[r] == HEREDOC)
				open_herdoc(&tmp, &r, head);
			r++;
		}
		tmp.plist = tmp.plist->next;
	}
}

void	run_buil_red(t_variable *my_env, t_info *info, int *ptr)
{
	int	count;

	count = *ptr;
	cherch_output(info);
	if (g_general->error_red == 0)
	{
		my_env = exec_builtin(my_env, info, count);
		g_general->exit_status = 0;
	}
}
