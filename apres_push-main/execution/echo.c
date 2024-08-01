/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:09:29 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/01 20:45:33 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_n(char *str, int *flag)
{
	int	i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (!str[i])
		*flag = 1;
	else
		*flag = 0;
}

void	print_echo(char **av, int ac, int *ptr, int *ptr1)
{
	int	i;
	int	flag1;

	i = *ptr;
	flag1 = *ptr1;
	while (av[i])
	{
		printf("%s", av[i++]);
		if (i < ac)
			printf(" ");
	}
	if (flag1)
		printf("\n");
}

void	builtin_echo(int ac, char **av)
{
	int	i;
	int	j;
	int	flag;
	int	flag1;

	i = 1;
	flag = 0;
	flag1 = 1;
	j = 0;
	while (av[i])
	{
		if (av[i][j] == '-')
		{
			check_n(av[i], &flag);
			if (flag)
				flag1 = 0;
		}
		else
			flag = 0;
		if (flag)
			i++;
		else
			break ;
	}
	print_echo(av, ac, &i, &flag1);
}

void	echo_dernier_word(t_variable	*pwd_env,
		t_variable *my_env, t_info *info, int count)
{
	pwd_env = check_variable(my_env, "_", info->var);
	if (pwd_env != NULL)
	{
		free(pwd_env->valeur);
		pwd_env->valeur = ft_strdup1(info->plist->parts[count - 1]);
	}
}

int	error_cd(char **av)
{
	if (access(av[1], F_OK) != 0)
	{
		write(2, av[1], ft_strlen(av[1]));
		ft_putstr(" : No such file or directory\n", 2);
		g_general->exit_status = 1;
		return (0);
	}
	if (access(av[1], X_OK) != 0)
	{
		write(2, av[1], ft_strlen(av[1]));
		ft_putstr(" : permission denied \n", 2);
		g_general->exit_status = 1;
		return (0);
	}
	return (1);
}
