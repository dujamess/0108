/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:50:13 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/31 23:05:56 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit1(char *c)
{
	int	i;

	i = 0;
	if (c && (c[i] == '+' || c[i] == '-'))
		i++;
	while (c && c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c && c[i] == '\0')
		return (1);
	else
		return (0);
}

void	exit_multiple(char **av, int ac)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_isdigit1(av[i]) == 0)
			break ;
		i++;
	}
	if (ac == i || (ft_isdigit1(av[1]) == 1))
	{
		ft_putstr("exit\n", 2);
		write(2, "exit: too many arguments\n", 26);
		g_general->exit_status = 1;
	}
	else
	{
		write(2, "exit: ", 7);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": numeric argument required\n", 29);
		g_general->exit_status = 2;
		free_all(g_general->info);
		exit(g_general->exit_status);
	}
}

void	print_exit(char **av)
{
	write(2, "exit: ", 7);
	write(2, av[1], ft_strlen(av[1]));
	write(2, ": numeric argument required\n", 29);
}

void	exit_error(char **av)
{
	print_exit(av);
	g_general->exit_status = 2;
	free_all(g_general->info);
	exit(g_general->exit_status);
}

void	builtin_exit(int ac, char **av)
{
	ac = 0;
	while (av[ac])
		ac++;
	if (ac == 1)
	{
		g_general->exit_status = 0;
		free_all(g_general->info);
		exit(g_general->exit_status);
	}
	else if (ac == 2)
	{
		check_error_max_exit(av);
		g_general->exit_status = ft_atoi1(av[1]);
		free_all(g_general->info);
		exit(g_general->exit_status);
	}
	else if (ac > 2)
		exit_multiple(av, ac);
}
