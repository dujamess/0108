/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:29:23 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 17:17:15 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cherch_input(t_info *info)
{
	int	i;

	i = 0;
	while (info->plist->reds && info->plist->reds[i])
	{
		if (info->plist->types[i] == I_RED)
			open_input_redirection(info, &i);
		i++;
	}
}

void	open_o_red(t_info *info, int *ptr)
{
	int		i;
	char	*str;
	int		expanded;

	expanded = 0;
	i = *ptr;
	if (info->plist->reds[i + 1])
	{
		str = mini_expand(info->plist->reds[i + 1], info, &expanded);
		if (!str || (count_words(str) > 1 && expanded))
		{
			ft_putstr("ambiguous redirect\n", 2);
			exit(1);
		}
		info->plist->reds[i + 1] = str;
		if (info->fd1 != 1)
			close(info->fd1);
		info->fd1 = open(info->plist->reds[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (info->fd1 == -1)
			ft_perror();
		else
		{
			dup2(info->fd1, STDOUT_FILENO);
			close(info->fd1);	
		}
	}
}

void	output_append(t_info *info, int *ptr)
{
	int		i;
	char	*str;
	int		expanded;

	expanded = 0;
	i = *ptr;
	if (info->fd1 != 1)
		close(info->fd1);
	str = mini_expand(info->plist->reds[i + 1], info, &expanded);
	if (!str || (count_words(str) > 1 && expanded))
	{
		ft_putstr("ambiguous redirect\n", 2);
		exit(1);
	}
	info->plist->reds[i + 1] = str;
	info->fd1 = open(info->plist->reds[i + 1],
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (info->fd1 == -1)
		ft_perror();
	dup2(info->fd1, STDOUT_FILENO);
	close(info->fd1);
}

void	cherch_output(t_info *info)
{
	int	i;

	i = 0;
	while (info->plist->reds && info->plist->reds[i] && g_general->error_red == 0)
	{
		if (info->plist->types[i] == O_RED)
			open_o_red(info, &i);
		else if (info->plist->types[i] == A_RED)
		{
			if (info->plist->reds[i + 1])
				output_append(info, &i);
		}
		else if (info->plist->types[i] == I_RED)
			open_input_redirection(info, &i);
		i++;
	}
}

void	check_commande(t_info *info, char **env)
{
	char	*s;

	s = NULL;
	ft_stat(info, info->plist->parts[0]);
	if (ft_strchr(info->plist->parts[0], '/') == NULL)
	{
		s = join_commande_path1(info->path, info->plist->parts[0]);
		if (s == NULL)
		{
			write_command_not_found(info);
			exit(g_general->exit_status);
		}
	}
	else
		s = info->plist->parts[0];
	check_execve(info, env, s);
	exit(g_general->exit_status);
}
