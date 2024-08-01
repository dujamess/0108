/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permessio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:36:13 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 23:44:19 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_command_not_found(t_info *info)
{
	write(2, info->plist->parts[0],
		ft_strlen(info->plist->parts[0]));
	write(2, " : command not found", 20);
	write(2, "\n", 1);
	g_general->exit_status = 127;
}

void	write_permission_denied(t_info *info)
{
	ft_putstr(info->plist->parts[0], 2);
	write(2, ": permission denied", 20);
	write(2, "\n", 1);
	g_general->exit_status = 126;
}

int	check_slach(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->plist->parts[i])
	{
		j = 0;
		while (info->plist->parts[i][j])
		{
			if ((info->plist->parts[i][j] == '.')
				|| (info->plist->parts[i][j] == '/'))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	check_execve(t_info *info, char **env, char *s)
{
	if (execve(s, info->plist->parts, env) == -1)
	{
		g_general->exit_status = 127;
		perror(s);
	}
}
