/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:57:53 by mmondad           #+#    #+#             */
/*   Updated: 2024/08/01 17:23:37 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_general	*g_general;

void	run_minishell(t_variable **my_env, t_info *info,
		char **env_exec)
{
	int		count;
	t_file	*head ;

	head = NULL;
	open_herdoc_in_main(*info, &head);
	info->head_f = head;
	signal(SIGINT, handel);
	count = number_commande(*info);
	split_path(*my_env, info->path);
	g_general->g_env = *my_env;
	if ((check_is_builtin(info) == 1) && (info->plist->next == NULL))
	{
		save_pwd(info);
		if (info->plist->reds)
		{
			g_general->red = 1;
			command_builtin_redirection(info, *my_env, &count);
		}
		else
			run_builtin_final(my_env, info, count);
		return ;
	}
	else if (!g_general->exit_status)
		execution_cmd(*my_env, info, env_exec);
}

void	run1_minishell(t_info *info, t_variable **my_env)
{
	int	check;

	check = parsing(info);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	free_d((*my_env)->env_exec);
	(*my_env)->env_exec = return_env(*my_env);
	if (!check && info->plist)
		run_minishell(my_env, info, (*my_env)->env_exec);
}

void	minishell_execut(t_info *info)
{
	while (info->head_f)
	{
		unlink(info->head_f->file_name);
		info->head_f = info->head_f->next;
	}
	free_list(info, 0);
	free(info->tmp_line);
}

void	my_minishell(t_info *info, t_variable *my_env)
{
	while (1)
	{
		g_general->red = 0;
		g_general->error_red = 0;
		dup2(g_general->fd0,0);
		dup2(g_general->fd1,1);
		signals();
		init_info(my_env, info);
		run1_minishell(info, &my_env);
		minishell_execut(info);
	}
}

int	main(int argc, char **argv, char **penv)
{
	t_info		info;
	t_variable	*my_env;
	t_variable	*pwd_env;

	(void)argc;
	(void)argv;
	my_env = NULL;
	pwd_env = NULL;
	info.head_h = NULL;
	info.tmp_line = NULL;
	init_global_var(&info);
	my_env = set_env(my_env, penv);
	g_general->fd0 = dup(0);
	g_general->fd1 = dup(1);
	my_env->env_exec = NULL;
	info.path = malloc(sizeof(t_path));
	if (!info.path)
		return (1);
	info.path->var_path = NULL;
	info.var = malloc(sizeof(t_pwd));
	if (!info.var)
		return (1);
	info.var->pwd = NULL;
	augment_level_shlvl(my_env, &info);
	g_general->g_env = my_env;
	g_general->info = &info;
	my_minishell(&info, my_env);
}
