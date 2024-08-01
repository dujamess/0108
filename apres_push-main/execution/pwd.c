/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:31:07 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 21:10:59 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(char *var)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("%s\n", var);
	else
		printf("%s\n", pwd);
	free(pwd);
}

void	save_pwd(t_info *info)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	new_fnode(dir, info);
	if (dir)
	{
		free(info->var->pwd);
		info->var->pwd = getcwd(NULL, 0);
	}
}

void	ft_stat(t_info *info, char *s)
{
	int	j;

	(void)info;
	j = print_file_info(s);
	if (j == 0)
	{
		g_general->exit_status = 126;
		exit(g_general->exit_status);
	}
	else if (j == 1)
	{
		g_general->exit_status = 127;
		exit(g_general->exit_status);
	}
}

void	ft_perror(void)
{
	perror("minishell");
	g_general->exit_status = 1;
	g_general->error_red = 1;
	if (g_general->red != 1)
		exit(EXIT_FAILURE);
}

int	ft_atoi1(const char *str)
{
	int	signe;
	int	i;
	int	result;

	i = 0;
	result = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		signe = signe * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * signe);
}
