/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:33:51 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 00:33:01 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_multiple_commande(t_info *info, int *fd, int *prev_fd)
{
	if (info->fd0 == 0)
	{
		close(fd[0]);
		if (prev_fd != NULL)
		{
			dup2(prev_fd[0], STDIN_FILENO);
			close(prev_fd[0]);
		}
	}
	if (info->fd1 == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (info->fd0 != 0)
		close(fd[0]);
	if (info->fd1 != 1)
		close(fd[1]);
}

void	parent_child_multiple(int *prev_fd, int *fd)
{
	close(fd[1]);
	if (prev_fd != NULL)
		close(prev_fd[0]);
	prev_fd[0] = fd[0];
}

void	child_process(t_info *info, char **en, int *prev_fd, t_variable *env)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		cherch_output(info);
		if (g_general->error_red == 1)
			exit(1);
		dup_multiple_commande(info, fd, prev_fd);
		if (check_is_builtin(info) == 1)
		{
			env = exec_builtin(env, info, info->lst_size);
			g_general->g_env = env;
			exit(g_general->exit_status);
		}
		else if (info->plist->parts[0])
			check_commande(info, en);
		else
			exit(0);
	}
	else
		parent_child_multiple(prev_fd, fd);
}

void	dup_input_1(t_info *info, int *fd)
{
	if (info->fd0 == 0)
	{
		if (fd[0] != -1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
	}
}

void	child_ps_1_commande(t_info *info, char **en, t_variable *env, int *fd)
{
	cherch_output(info);
	if (g_general->error_red == 1)
		exit(1);
	dup_input_1(info, fd);
	if (info->plist->parts[0])
	{
		if (check_is_builtin(info) == 1)
		{
			env = exec_builtin(env, info, info->lst_size);
			g_general->g_env = env;
			exit(g_general->exit_status);
		}
		else if (info->plist->parts[0])
			check_commande(info, en);
	}
	else
	{
		g_general->exit_status = 0;
		exit(g_general->exit_status);
	}
}
