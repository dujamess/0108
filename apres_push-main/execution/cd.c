/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:17:36 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 17:47:15 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_path(t_variable *pwd_env, t_pwd *var, t_variable *my_env, char *oldpwd)
{
	char	*pwd;

	pwd = NULL;
	if (check_pwd(my_env, pwd_env, pwd, var) == 0)
	{
		free(oldpwd);
		return (0);
	}
	pwd_env = check_variable(my_env, "OLDPWD", var);
	if (pwd_env == NULL)
		return (0);
	free(pwd_env->valeur);
	pwd_env->valeur = oldpwd;
	return (1);
}

int	cd_home(t_variable *my_env, t_pwd *var)
{
	char		*oldpwd;
	char		*pwd;
	t_variable	*path;
	t_variable	*pwd_env;

	path = NULL;
	pwd = NULL;
	pwd_env = NULL;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd != NULL)
		var->oldpwd = oldpwd;
	if (oldpwd == NULL)
		oldpwd = var->oldpwd;
	if (check_home(my_env, path, var) == 0)
		return (0);
	if (check_pwd(my_env, pwd_env, pwd, var) == 0)
		return (0);
	if (check_oldpwd(pwd_env, my_env, oldpwd, var) == 0)
		return (0);
	return (1);
}

int	run_cd(t_pwd *var, t_variable *my_env, char **av)
{
	char		*oldpwd;
	char		*pwd;
	t_variable	*path;
	t_variable	*pwd_env;

	path = NULL;
	pwd = NULL;
	pwd_env = NULL;
	if (error_cd(av) == 0)
		return (0);
	oldpwd = getcwd(NULL, 0);
	chdir(av[1]);
	if (cd_path(pwd_env, var, my_env, oldpwd) == 0)
		return (0);
	return (1);
}

int	print_cd(int ac, char **av, t_variable *my_env, t_pwd *var)
{
	(void)ac;
	if (!run_cd(var, my_env, av))
		return (0);
	return (1);
	g_general->exit_status = 0;
}

int	builtin_cd(int ac, char **av, t_variable *my_env, t_pwd *var)
{
	char		*pwd;
	t_variable	*path;
	t_variable	*pwd_env;

	path = NULL;
	pwd = NULL;
	pwd_env = NULL;
	ac = 0;
	while (av[ac])
		ac++;
	if (ac == 1)
	{
		if (cd_home(my_env, var) == 0)
			g_general->exit_status = 1;
		else
			g_general->exit_status = 0;
	}
	else if (ac == 2)
		print_cd(ac, av, my_env, var);
	else
	{
		ft_putstr(" too many arguments\n", 2);
		g_general->exit_status = 1;
	}
	return (0);
}
