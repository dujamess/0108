/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:02:07 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/30 14:54:14 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin_final(t_variable **my_env, t_info *info, int count)
{
	*my_env = exec_builtin(*my_env, info, count);
	g_general->g_env = *my_env;
}

int	check_is_builtin(t_info *info)
{
	if ((info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "pwd") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "env") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "echo") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "cd") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "exit") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "unset") == 0)
		|| (info->plist->parts[0]
			&& ft_strcmp(info->plist->parts[0], "export") == 0))
		return (1);
	return (0);
}

void	exec_builtin1(t_variable *my_env, t_info *info, int s)
{
	if (info->plist->parts[0] && ft_strcmp(info->plist->parts[0], "pwd") == 0)
		builtin_pwd(info->var->pwd);
	else if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "env") == 0)
		print_env1(my_env, 0);
	else if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "echo") == 0)
	{
		s = 0;
		while (info->plist->parts[s])
			s++;
		builtin_echo(s, info->plist->parts);
	}
	else if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "cd") == 0)
	{
		if (info->plist->parts[1] == NULL)
			s = 1;
		else
			s = 2;
		builtin_cd(s, info->plist->parts, my_env, info->var);
	}
}

void	exec_builtin2(t_variable *my_env, t_info *info, int s)
{
	if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "exit") == 0)
		builtin_exit(s, info->plist->parts);
	else if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "export") == 0
		&& info->plist->parts[1] == NULL)
		print_env1(my_env, 1);
}

t_variable	*exec_builtin(t_variable *my_env, t_info *info, int s)
{
	t_variable	*var;

	exec_builtin1(my_env, info, s);
	exec_builtin2(my_env, info, s);
	if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "unset") == 0)
	{
		var = my_env;
		my_env = builtin_unset(info->plist->parts, my_env);
		free_vars(var);
	}
	else if (info->plist->parts[0]
		&& ft_strcmp(info->plist->parts[0], "export") == 0
		&& info->plist->parts[1])
	{
		var = my_env;
		my_env = builtin_export(info->plist->parts, my_env);
		free_vars(var);
	}
	return (my_env);
}
