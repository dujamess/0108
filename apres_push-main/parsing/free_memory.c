/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:59:32 by mmondad           #+#    #+#             */
/*   Updated: 2024/07/30 18:03:50 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_vars(t_variable *list)
{
	int	i;

	i = 0;
	while (list && list[i].nom)
	{
		free(list[i].valeur);
		free(list[i].nom);
		free(list[i].env_join);
		i++;
	}
	free(list);
}

void	free_list(t_info	*info, int i)
{
	t_heapnode	*tmp;

	while (info->head_h != NULL)
	{
		tmp = info->head_h;
		info->head_h = info->head_h->next;
		free(tmp->data);
		free(tmp);
	}
	info->head_h = NULL;
	if (i)
		print_error("allocation_error\n", g_general->exit_status, 2);
}

void	*allocate(t_info *info, size_t size)
{
	char	*str;

	str = ft_calloc(1, size);
	new_fnode(str, info);
	return (str);
}

void	free_all(t_info *info)
{
	free(info->var->pwd);
	free_d(info->path->var_path);
	free_d(info->env->env_exec);
	free_vars(info->env);
	free_list(info, 0);
	free(info->tmp_line);
}
