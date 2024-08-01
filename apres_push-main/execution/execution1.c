/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:16:23 by khmessah          #+#    #+#             */
/*   Updated: 2024/07/27 13:19:33 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_string(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	split_path(t_variable *env, t_path *path)
{
	int		i;
	int		h;
	char	*v;

	h = 0;
	i = -1;
	if (path->var_path)
		free_d(path->var_path);
	path->var_path = NULL;
	while (env[++i].nom)
	{
		if (ft_strcmp1(env[i].nom, "PATH") == 0)
		{
			path->var_path = ft_split1(env[i].valeur, ':');
			while (path->var_path[h])
			{
				v = path->var_path[h];
				path->var_path[h] = ft_strjoin1(path->var_path[h], "/");
				free(v);
				h++;
			}
			return (1);
		}
	}
	return (0);
}

char	*join_commande_path1(t_path *path, char *av)
{
	char	*path_commande;
	int		h;

	h = 0;
	while (path->var_path && path->var_path[h])
	{
		path_commande = ft_strjoin1(path->var_path[h], av);
		if ((access(path_commande, F_OK) == 0)
			&& (access(path_commande, X_OK) == 0))
			return (path_commande);
		free(path_commande);
		h++;
	}
	return (NULL);
}

void	handle_child_signal(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	exit(130);
}
