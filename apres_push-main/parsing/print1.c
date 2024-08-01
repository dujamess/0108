/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:02:36 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 23:15:35 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stx_message(char *token, char c)
{
	ft_putstr(SYNTAX_ERROR, 2);
	if (c)
		write(1, &c, 1);
	else
		ft_putstr(token, 2);
	ft_putstr("'\n", 2);
}

int	print_file_info(char *path)
{
	struct stat	file_stat;

	if ((ft_strchr1(path, '/') != NULL) && (access(path,F_OK) == -1))
	{
		ft_putstr(path, 2);
		ft_putstr(": No such file or directory\n", 2);
		return (1);
	}
	else if (ft_strchr1(path, '/') != NULL && access(path,F_OK) != -1)
	{
		stat(path, &file_stat);
		if (S_ISREG(file_stat.st_mode) && access(path, X_OK) != -1)
			return (0);
		else if (S_ISREG(file_stat.st_mode) && access(path, X_OK) == -1)
		{
			ft_putstr(path, 2);
			ft_putstr(": Permission denied\n", 2);
			return (0);
		}
		else if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr(path, 2);
			ft_putstr(": Is a directory\n", 2);
			return (0);
		}
	}
	return (2);
}
