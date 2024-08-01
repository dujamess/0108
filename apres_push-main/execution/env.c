/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:55:13 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 17:57:15 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print(t_variable *my_env, int *ptr)
{
	int			i;
	char		c;

	i = *ptr;
	c = '\"';
	sort_env(my_env);
	if (ft_strcmp1(my_env[i].valeur, "") == 0 && my_env[i].flag_ega == 0)
		printf("declare -x %s%s\n", my_env[i].nom, my_env[i].valeur);
	else if (ft_strcmp1(my_env[i].valeur, "") == 0 && my_env[i].flag_ega == 1)
		printf("declare -x %s=%c%s%c\n", my_env[i].nom, c, my_env[i].valeur, c);
	else
		printf("declare -x %s=%c%s%c\n",
			my_env[i].nom, c, my_env[i].valeur, c);
}

void	print_env1(t_variable *my_env, int flag)
{
	int			i;

	i = 0;
	while (my_env && my_env[i].nom != NULL && my_env[i].valeur != NULL)
	{
		if (flag == 0 && my_env[i].flag_print == 0)
			printf("%s=%s\n", my_env[i].nom, my_env[i].valeur);
		else if (flag == 1)
			export_print(my_env, &i);
		i++;
	}
}

int	count_env(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

t_variable	split_env(char *env_line)
{
	t_variable	var;
	char		*delimiter_pos;
	int			nom_length;

	var.env_join = ft_strdup1(env_line);
	delimiter_pos = ft_strchr1(env_line, '=');
	if (delimiter_pos != NULL)
	{
		nom_length = delimiter_pos - env_line;
		var.nom = (char *)ft_calloc(nom_length + 1, 1);
		ft_strncpy1(var.nom, env_line, nom_length);
		var.valeur = ft_strdup1(delimiter_pos + 1);
		g_general->ptr = var.valeur;
		var.flag_print = 0;
		var.n = position_egal(env_line);
	}
	else
	{
		var.nom = ft_strdup1(env_line);
		var.flag_print = 0;
		var.n = position_egal(env_line);
		var.valeur = NULL;
	}
	return (var);
}

t_variable	*builtin_env(char **env)
{
	int			env_count;
	t_variable	*env_vars;
	int			i;

	env_count = count_env(env);
	env_vars = (t_variable *)malloc((env_count + 1) * sizeof(t_variable));
	if (!env_vars)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		env_vars[i] = split_env(env[i]);
		i++;
	}
	env_vars[i].nom = NULL;
	env_vars[i].valeur = NULL;
	env_vars[i].env_join = NULL;
	return (env_vars);
}
